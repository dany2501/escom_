/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.net.*;
import java.io.*;

/**
 *
 * @author dany2
 */
public class Servidor {
    
    public static void main(String[] args) {
        // TODO code application logic here
        
        try{
            
            ServerSocket ss = new ServerSocket(7000);
            
            System.out.println("Esperando conexiones");
            
            for(;;){
                Socket s = ss.accept();
                
                System.out.println("Conexión establecida desde "+s.getInetAddress()+" : "+s.getPort());
                
                DataInputStream dis = new DataInputStream(s.getInputStream());
                
                byte[] b = new byte[1024];
                
                String nombre = dis.readUTF();
                System.out.println("Recibimos el archivo: "+nombre);
                long tam = dis.readLong();
                DataOutputStream dos = new DataOutputStream(new FileOutputStream(nombre));
                long recibidos = 0;
                
                int n, porcentaje;
                
                
                while (recibidos < tam){
                    n = dis.read(b);
                    dos.write(b,0,n);
                    dos.flush();
                    recibidos += n;
                    porcentaje = (int)(recibidos*100/tam);
                    
                    
                }
                dos.close();
                dis.close();
            }
            
        }catch(Exception e){
            e.printStackTrace();
        }
        
        
    }
}
