import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Matrices {
  
    private static final int PUERTO = 50000;//Puerto de las máquinas virtuales donde se comunican las máquinas
    private static final String[] NODOS = {"20.168.75.198","20.38.3.10","20.122.47.248"};//Maquinas virtuales en Azure
    public static final int NUM_NODOS = NODOS.length; //Cantidad de nodos del sistema
    public static int numeroNodo;//Identificador del nodo
    public static int tamMatriz;//Tamaño de la matriz cuadrada

    public static void main(String[] args) throws Exception{
        if(args.length != 2){
            System.err.println("Asigne un numero al nodo y el tamaño de la matriz cuadrada");
            System.exit(1);
        }
        tamMatriz = NUM_NODOS;
        try{
            numeroNodo = Integer.parseInt(args[0]);
            tamMatriz = Integer.parseInt(args[1]);
        }
        catch(NumberFormatException e){
            System.err.println(e.getMessage());
            System.exit(1);
        }
        if(numeroNodo < 0 || numeroNodo > NUM_NODOS) System.err.println("Numero de nodo fuera del rango [0,"+NUM_NODOS+"]");
        else if(tamMatriz <= 0 || tamMatriz%NUM_NODOS!=0) System.err.println("El tamaño de la matriz debe ser múltiplo de "+NUM_NODOS);
        
        if(numeroNodo == 0){
            nodoLocal();
        }
        else{
            nodosEnNube();
        }
    }
    static void read(DataInputStream f, byte[] b,int posicion, int longitud) throws Exception{
        while(longitud > 0){
            int n = f.read(b,posicion,longitud);
            posicion += n;
            longitud -= n;
        }
    }
    
    public static void nodoLocal() throws Exception{
        //Incializar las matrices
        float[][] A = new float[tamMatriz][tamMatriz];
        float[][] B = new float[tamMatriz][tamMatriz];
        float[][] C = new float[tamMatriz][tamMatriz];
        for(int i=0; i<tamMatriz; i++){
            for(int j=0; j<tamMatriz; j++){
                A[i][j] = 2*i+j;
                B[i][j] = 3*i-j;
            }
        }
        //Trasponer la matriz B
        for(int i=0; i<tamMatriz; i++){
            for(int j=0; j<i; j++){
                float x = B[i][j];
                B[i][j] = B[j][i];
                B[j][i] = x;
            }
        }
        Socket[] conexion = new Socket[NUM_NODOS];
        DataOutputStream[] salida = new DataOutputStream[NUM_NODOS];
        DataInputStream[] entrada = new DataInputStream[NUM_NODOS];
        //Conectar el nodo 0 (local) a los demas nodos (Maquinas virtuales en Azure)
        for(int i=0; i<NUM_NODOS; i++){
            //Reintento de conexion a cada nodo
            for(;;){
                try{
                    /*PARA PRUEBAS LOCALES SE LE SUMA i AL PUERTO */
                    //conexion[i] = new Socket(NODOS[i],PUERTO+i);
                    System.err.println("Conectando a la ip "+ NODOS[i]);
                    System.err.println("Puerto "+ String.valueOf(PUERTO));
                    conexion[i] = new Socket(NODOS[i],PUERTO);
                    salida[i] = new DataOutputStream(conexion[i].getOutputStream());
                    entrada[i] = new DataInputStream(conexion[i].getInputStream());
                    break;
                }
                catch(Exception e){
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e1) {
                        System.err.println("Error al esperar: "+e1.getMessage());
                    }
                }
            }
            
        }
        ByteBuffer seccionA = ByteBuffer.allocate(tamMatriz*(tamMatriz/NUM_NODOS)*Float.BYTES);
        ByteBuffer[] seccionesB = new ByteBuffer[NUM_NODOS];
        for(int i=0; i<NUM_NODOS; i++){
            seccionesB[i] = ByteBuffer.allocate(tamMatriz*(tamMatriz/NUM_NODOS)*Float.BYTES);
        }
        for(int i=0; i<NUM_NODOS; i++){
            for(int j=tamMatriz/NUM_NODOS*i; j<tamMatriz/NUM_NODOS*(i+1); j++){
                for(int k=0; k<tamMatriz; k++){
                    seccionesB[i].putFloat(B[j][k]);
                }
            }
        }

        //Enviar matrices
        for(int i=0; i<NUM_NODOS; i++){
            //Pon los valores de la matriz A en el buffer dependiendo del nodo
            for(int j=tamMatriz/NUM_NODOS*i; j<tamMatriz/NUM_NODOS*(i+1); j++){
                for(int k=0; k<tamMatriz; k++){
                    seccionA.putFloat(A[j][k]);
                }
            }
            //Envia la sección A al nodo correspondiente
            salida[i].write(seccionA.array(), 0, seccionA.capacity());
            //Envia las secciones de la matriz B
            for(int j=0; j<NUM_NODOS; j++){
                salida[i].write(seccionesB[j].array(), 0, seccionesB[j].capacity());
            }
            seccionA.clear();
        }

        //Recibir matrices
        byte[] bytesArrayMatC = new byte[(tamMatriz/NUM_NODOS)*(tamMatriz/NUM_NODOS)*Float.BYTES];
        ByteBuffer bufferMatC;
        for(int i=0; i<NUM_NODOS; i++){
            for(int j=0; j<NUM_NODOS; j++){ //Recibe NUM_NODOS² submatices de tamaño tamMatriz/NUM_NODOS
                read(entrada[i], bytesArrayMatC, 0, bytesArrayMatC.length);
                bufferMatC = ByteBuffer.wrap(bytesArrayMatC);
                for(int k=0; k<tamMatriz/NUM_NODOS; k++){
                    for(int l=0; l<tamMatriz/NUM_NODOS; l++){ //Carga en la matriz C los valores de la submatrices devueltas
                        C[k+(tamMatriz/NUM_NODOS*i)][l+(tamMatriz/NUM_NODOS*j)] = bufferMatC.getFloat();
                    }
                }
            }
        }        
        //Calcular el checksum
        float checksum=0;
        for(int i=0; i<tamMatriz; i++){
            for(int j=0; j<tamMatriz; j++){
                checksum += C[i][j];
            }
        }
        //Desplegar el checksum
        System.out.println("Checksum de la suma de matrices: " + checksum);
        //Si N=12 desplegar matrices A,B y C
        if(tamMatriz==12){
            System.out.println("\tMatriz A:");
            imprime_matriz(A,tamMatriz, tamMatriz);
            System.out.println();
            System.out.println("\tMatriz B:");
            //Trasponer la matriz B
            imprime_matriz(B,tamMatriz, tamMatriz);
            System.out.println();
            System.out.println("\tMatriz C:");
            imprime_matriz(C,tamMatriz, tamMatriz);
        }

        for(int i=0; i<NUM_NODOS; i++){
            try{
                conexion[i].close();
            }
            catch(Exception e){
                System.err.println(e.getMessage());
            }
        }
    }
    public static void nodosEnNube() throws Exception{
        float[][] seccionA = new float[tamMatriz/NUM_NODOS][tamMatriz];
        float[][][] seccionesB = new float[NUM_NODOS][tamMatriz/NUM_NODOS][tamMatriz];
        float[][][] resultadosC = new float[NUM_NODOS][tamMatriz/NUM_NODOS][tamMatriz/NUM_NODOS];
        ServerSocket servidor;
        Socket conexion;
        DataOutputStream salida=null;
        DataInputStream entrada=null;
        try {
            /*Para preubas locales se le suma el numero que le corresponde al puerto */
            //servidor = new ServerSocket(PUERTO+numeroNodo-1);
            servidor = new ServerSocket(PUERTO);
            conexion = servidor.accept();//Espera la conexion con el nodo 0
            salida = new DataOutputStream(conexion.getOutputStream());
            entrada = new DataInputStream(conexion.getInputStream());
        }
        catch(IOException e){
            System.err.println(e.getMessage());
            System.exit(1);
        }
        byte[] bytesMatA = new byte[tamMatriz*(tamMatriz/NUM_NODOS)*Float.BYTES];
        byte[] bytesSeccionMatB = new byte[tamMatriz*(tamMatriz/NUM_NODOS)*Float.BYTES];
        //Recibe la seccion de la matriz A del nodo que le corresponde
        read(entrada, bytesMatA, 0, bytesMatA.length);
        ByteBuffer bufferMatA = ByteBuffer.wrap(bytesMatA);
        for(int i=0; i<tamMatriz/NUM_NODOS; i++){
            for(int j=0; j<tamMatriz; j++){
                seccionA[i][j] = bufferMatA.getFloat();
            }
        }
        //Recibe las secciones de la matriz B
        ByteBuffer bufferSeccionMatB;
        for(int i=0; i<NUM_NODOS; i++){
            read(entrada, bytesSeccionMatB, 0, bytesSeccionMatB.length);
            bufferSeccionMatB = ByteBuffer.wrap(bytesSeccionMatB);
            for(int j=0; j<tamMatriz/NUM_NODOS; j++){
                for(int k=0; k<tamMatriz; k++){
                    seccionesB[i][j][k] = bufferSeccionMatB.getFloat();
                }
            }
        }
        //Realizar los productos por renglón
        for(int i=0; i<NUM_NODOS; i++){//Submatrices Ci que se enviarán
            for(int j=0; j<tamMatriz/NUM_NODOS; j++){//Cada reng{on de la sección de la matriz A
                for(int k=0; k<tamMatriz/NUM_NODOS; k++){//Cada renglón de la sección de la matriz B correspondiente
                    for(int l=0; l<tamMatriz; l++){//Cada número de un renglón
                        resultadosC[i][j][k] += seccionA[j][l]*seccionesB[i][k][l];
                    }
                }
            }
        }
        //Enviar las matrices resultantes
        ByteBuffer bufferResultadosMatC = ByteBuffer.allocate((tamMatriz/NUM_NODOS)*(tamMatriz/NUM_NODOS)*Float.BYTES);
        for(int i=0; i<NUM_NODOS; i++){
            //Pon los valores de la matriz resultante C en el buffer dependiendo del nodo
            for(int j=0; j<tamMatriz/NUM_NODOS; j++){
                for(int k=0; k<tamMatriz/NUM_NODOS; k++){
                    bufferResultadosMatC.putFloat(resultadosC[i][j][k]);
                }
            }
            //Envia la matriz C resultante al nodo
            salida.write(bufferResultadosMatC.array(), 0, bufferResultadosMatC.capacity());
            bufferResultadosMatC.clear();
        }
    }

    //funcion para imprimir la matriz
    public static void imprime_matriz(float[][] Matriz,int f,int c){
        for(int i=0;i<f;i++){
            for(int j=0;j<c;j++){
                System.out.print("\t" + Matriz[i][j]);
            }
            System.out.println();
        }
    }
}
