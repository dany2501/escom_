/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import javax.swing.JFileChooser;
import java.net.*;
import java.io.*;
import java.util.*;

/**
 *
 * @author dany2
 */
public class Cliente {

    /**
     * @param args the command line arguments
     */


    private List<File> file = new ArrayList<File>();
    private static JFileChooser jf = new JFileChooser("/Users/danielhernandez/Downloads/Flujo_maximo.pdf");
    public static void main(String[] args) {
        // TODO code application logic here
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Escribe la direccion del servidor");
            String host = br.readLine();
            System.out.println("\nEscribe el puerto");
            int pto = Integer.parseInt(br.readLine());

                File[] files = jf.getSelectedFiles();
                System.out.println(jf);
                for (File f : files){
                    Socket s = new Socket(host,pto);
                    String archivo = f.getAbsolutePath();
                    String nombre = f.getName();
                    long tam = f.length();

                    DataOutputStream dos = new DataOutputStream(s.getOutputStream());
                    DataInputStream dis = new DataInputStream(new FileInputStream(archivo));

                    dos.writeUTF(nombre);
                    dos.flush();

                    dos.writeLong(tam);
                    dos.flush();


                    byte [] b = new byte[1024];

                    long enviados = 0;
                    int porcentaje,n;
                    while (enviados < tam){
                        n = dis.read(b);
                        dos.write(b,0,n);
                        dos.flush();
                        enviados += n;
                        porcentaje = (int)(enviados*100/tam);

                    }

                    System.out.println("\nArchivo enviado");
                    dos.close();
                    dis.close();
                    s.close();
                }
                
            
            
            
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
}
