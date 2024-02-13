import java.io.*;
import java.net.*;
import javax.net.ssl.*;

public class SecureClientGet {
    public static void main(String[] args) {
        if (args.length != 3) {
            System.err.println("Uso: java ClienteSSL <ip_servidor> <puerto> <archivo>");
            System.exit(1);
        }

        String host = args[0];
        int puerto = Integer.parseInt(args[1]);
        String archivo = args[2];

        try {
            // Crear el socket SSL
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket socket = (SSLSocket) factory.createSocket(host, puerto);

            // Enviar petición GET y nombre del archivo
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println("GET " + archivo);

            // Recibir respuesta del servidor
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String respuesta = in.readLine();
            if (!respuesta.equals("OK")) {
                System.err.println("Error en la respuesta del servidor: " + respuesta);
                System.exit(1);
            }

            // Recibir longitud del archivo
            long longitud = Long.parseLong(in.readLine());

            // Recibir contenido del archivo
            byte[] contenido = new byte[(int) longitud];
            DataInputStream dis = new DataInputStream(socket.getInputStream());
            dis.readFully(contenido);

            // Escribir archivo en disco local
            File archivoLocal = new File(archivo);
            FileOutputStream fos = new FileOutputStream(archivoLocal);
            fos.write(contenido);
            fos.close();

            // Mostrar mensaje de éxito
            System.out.println("Archivo recibido con éxito: " + archivoLocal.getAbsolutePath());

            // Cerrar conexión
            socket.close();
        } catch (IOException e) {
            System.err.println("Error de E/S: " + e.getMessage());
            System.exit(1);
        }
    }
}
