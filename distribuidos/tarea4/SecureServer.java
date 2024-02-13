import java.io.*;
import java.net.*;
import javax.net.ssl.*;

public class SecureServer {
    private static final int PORT = 8888;

    public static void main(String[] args) throws IOException{
        System.setProperty("javax.net.ssl.keyStore","keystore_servidor.jks");
        System.setProperty("javax.net.ssl.keyStorePassword","hecd010225");
        SSLServerSocketFactory sslssf = (SSLServerSocketFactory) SSLServerSocketFactory.getDefault();
        try (SSLServerSocket serverSocket = (SSLServerSocket) sslssf.createServerSocket(PORT)) {
            serverSocket.setNeedClientAuth(true);

            while (true) {
                Socket socket = serverSocket.accept();
                new Thread(() -> handleRequest(socket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();
        String request = in.readLine();
        if (request.startsWith("GET")) {
            handleGetRequest(request, out);
        } else if (request.startsWith("PUT")) {
            handlePutRequest(request, clientSocket.getInputStream(), out);
        } else {
            out.write("ERROR".getBytes());
        }
        out.flush();
        clientSocket.close();
    }


    private static void handleGetRequest(String request, OutputStream out) throws IOException {
    String[] parts = request.split("\\s+");
    String fileName = parts[1];
    File file = new File(fileName);
    if (file.exists()) {
        FileInputStream fis = new FileInputStream(file);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        byte[] buffer = new byte[1024];
        int bytesRead;
        while ((bytesRead = fis.read(buffer)) != -1) {
            bos.write(buffer, 0, bytesRead);
        }
        byte[] content = bos.toByteArray();
        out.write("OK".getBytes());
        out.write(String.valueOf(content.length).getBytes());
        out.write(content);
    } else {
        out.write("ERROR".getBytes());
    }
}

    private static void handlePutRequest(String request, InputStream in, OutputStream out) throws IOException {
        String[] parts = request.split("\\s+");
        String fileName = parts[1];
        int length = Integer.parseInt(parts[2]);
        File file = new File(fileName);
        FileOutputStream fos = new FileOutputStream(file);
        byte[] content = new byte[length];
        int bytesRead;
        int totalBytesRead = 0;
        while (totalBytesRead < length && (bytesRead = in.read(content, totalBytesRead, length - totalBytesRead)) != -1) {
            totalBytesRead += bytesRead;
        }
        if (totalBytesRead == length) {
            fos.write(content);
            fos.close();
            out.write("OK".getBytes());
        } else {
            out.write("ERROR".getBytes());
        }
    }
}
