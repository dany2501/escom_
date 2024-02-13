import java.io.*;
import java.net.*;
import javax.net.ssl.*;
import java.security.*;

public class SecureSocketClient {
    private static final String TRUST_STORE_PATH = "keystore_cliente.jks"; // Ruta del truststore
    private static final String TRUST_STORE_PASSWORD = "hecd010225"; // Contraseña del truststore
    
    public static void main(String[] args) {
        if (args.length != 3) {
            System.err.println("Usage: java SecureSocketClient <server ip> <port> <file name>");
            System.exit(1);
        }
        
        String serverIP = args[0];
        int port = Integer.parseInt(args[1]);
        String fileName = args[2];
        
        // Leer el archivo del disco local
        File file = new File(fileName);
        if (!file.exists()) {
            System.err.println("Error: File " + fileName + " not found.");
            System.exit(1);
        }
        
        try {
            // Configurar SSL
            SSLContext sslContext = SSLContext.getInstance("TLS");
            KeyStore trustStore = KeyStore.getInstance(KeyStore.getDefaultType());
            FileInputStream trustStoreInputStream = new FileInputStream(TRUST_STORE_PATH);
            trustStore.load(trustStoreInputStream, TRUST_STORE_PASSWORD.toCharArray());
            TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
            trustManagerFactory.init(trustStore);
            sslContext.init(null, trustManagerFactory.getTrustManagers(), new SecureRandom());
            
            // Conectar con el servidor
            SSLSocketFactory sslSocketFactory = sslContext.getSocketFactory();
            SSLSocket socket = (SSLSocket) sslSocketFactory.createSocket(serverIP, port);
            socket.startHandshake();
            
            // Enviar petición PUT
            OutputStream outputStream = socket.getOutputStream();
            DataOutputStream dataOutputStream = new DataOutputStream(outputStream);
            String request = "PUT " + fileName + "\r\n";
            dataOutputStream.write(request.getBytes("UTF-8"));
            dataOutputStream.flush();
            
            // Enviar longitud del archivo
            long length = file.length();
            dataOutputStream.writeLong(length);
            dataOutputStream.flush();
            
            // Enviar contenido del archivo
            byte[] buffer = new byte[4096];
            FileInputStream fileInputStream = new FileInputStream(file);
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
                outputStream.flush();
            }
            fileInputStream.close();
            
            // Recibir respuesta del servidor
            InputStream inputStream = socket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            String response = dataInputStream.readUTF();
            
            // Verificar si el servidor respondió OK
            if (response.equals("OK")) {
                System.out.println("File " + fileName + " sent successfully.");
            } else {
                System.err.println("Error: Server failed to write file " + fileName + ".");
            }
            
            // Cerrar socket
            socket.close();
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
    }
}
