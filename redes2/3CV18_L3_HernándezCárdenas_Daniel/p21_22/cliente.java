import java.net.*;
import java.io.*;

public class cliente{
    public static void main(String args[]){
		try{
            //Definimos el puerto por el cual nos conectaremos al servidor
			int pto = 2000;
            //Definimos el host al cual nos vamos a conectar
			InetAddress dst = InetAddress.getByName("127.0.0.1");
            //Creamos nuestro socket de datagrama
			DatagramSocket cl = new DatagramSocket();
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			DataOutputStream dos = new DataOutputStream(baos);
            //Escribimos el entero
			dos.writeInt(4);
            //Limpiamos el buffer
			dos.flush();
            //Escribimos el flotante
			dos.writeFloat(4.1f);
            //Limpiamos el buffer
			dos.flush();
            //Escribimos el Long
			dos.writeLong(72);
            //Limpiamos el buffer
			dos.flush();
			byte[] b = baos.toByteArray();
			DatagramPacket p = new DatagramPacket(b,b.length,dst,pto);
            //Enviamos los datos
			cl.send(p);
            //Cerramos el socket
			cl.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}