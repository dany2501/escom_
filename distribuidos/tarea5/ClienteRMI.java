import java.rmi.Naming;
import java.rmi.RemoteException;

public class ClienteRMI{
    //Funcion para inicializar A y B
    static int partes=9;
    public static void inicializa_matrices(double[][] A, double[][] B,int N, int M) {
        for(int i=0;i<N;i++)
            for(int j=0;j<M;j++){
                A[i][j]=2*i+3*j;
            }
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++){
                B[i][j]=3*i-2*j;
            }
    }
    //Funcion para imprimir la matriz
    static void imprime_matriz(double[][] A,int N,int M){
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                System.out.print(A[i][j]+"\t");
            }
            System.out.println();
        }
    }
    //Funcion para realizar la transpuesta de B
    public static double[][] transpuesta(double[][] B, int N, int M){
        double[][] transpuesta= new double[N][M];
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                transpuesta[j][i] = B[i][j];
            }
        }
        return transpuesta;
    }
    //Funcion para separar la matriz
    public static double[][] separa_matriz(double[][] A,int inicio,int part){
        double[][] Mat = new double[A.length/part][A[0].length];
        for(int i=0;i<A.length/part;i++)
            for(int j=0;j<A[0].length;j++)
                Mat[i][j] = A[i+inicio][j];
        return Mat;
    }
    //Funcion para multiplicar matrices
    public static double[][] multiplica_matrices(double[][] A, double[][] B, int N,int M) {
        double [][] C = new double [N/9][N/9];
        for(int i=0;i<N/9;i++)
            for(int j=0;j<N/9;j++)
                for(int k=0;k<M;k++)
                    C[i][j] += A[i][k]*B[j][k];
        return C;
    }
    //Funcion para acompdar la matriz
    private static void acomoda_matriz(double[][] C, double[][] a, int renglon, int columna,int N) {
        for(int i=0;i<N/9;i++){
            for(int j=0;j<N/9;j++){
                C[i+renglon][j+columna] = a[i][j];
            }
        }
    }
    public static double checksum(double[][] m,int N,int M)throws RemoteException{
        double s=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                s+=m[i][j];
            }
        }
        return s;
    }
    //Class worker para que el nodo 0 trabaje en lo que recibe las respuestas de los demas.
    public static class Worker extends Thread{
        int N, M, posicion,n;
        double[][][] a,b,c;
        InterfaceRMI r;
        Worker(InterfaceRMI r,int N, int M, double[][][] a, double[][][] b, double[][][] c, int posicion, int n){
            this.r=r;
            this.N = N;
            this.M = M;
            this.a = a;
            this.b = b;
            this.c = c;
            this.posicion=posicion;
            this.n=n;
        }
        public void run(){
            Object obj= new Object();
            synchronized(obj){
                for(int i=0;i<partes*2;i++){
                    if(i<partes){
                        try {
                            c[i+partes*2*n]=r.multiplica_matrices(a[n*2], b[i], N, M);
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                    else{
                        try {
                            c[i+partes*2*n]=r.multiplica_matrices(a[(n*2)+1], b[i-9], N, M);
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
            
        }
    }
    //Main
    public static void main(String args[]) throws Exception {
        String url = "rmi://10.5.0.5/prueba";
        String url2 = "rmi://10.5.0.6/prueba";
        InterfaceRMI r = (InterfaceRMI)Naming.lookup(url);
        InterfaceRMI r2 = (InterfaceRMI)Naming.lookup(url2);
        int N=Integer.parseInt(args[0]);
        int M=Integer.parseInt(args[1]);
        double[][] A = new double[N][M];//Matriz A
        double[][] B = new double[M][N];//Matriz B
        double[][] Bt= new double[N][M];//Matriz B (transpuesta)
        double[][][] a= new double[partes][N/partes][M];//6 Matrices a (para guardar los dividos de A)
        double[][][] b= new double[partes][N/partes][M];//6 Matrices a (para guardar los dividos de A)
        double[][] C = new double[N][N];//Matriz C
        double[][][] c = new double[partes*partes][N/partes][N/partes];
        inicializa_matrices(A,B,N,M);//Inicializa matrices
        Bt=transpuesta(B,N,M);// traspuesta de B
        //Separa las matrices A y B
        for(int i=0;i<partes;i++){
            a[i]=separa_matriz(A,(N/partes)*i,partes);
            b[i]=separa_matriz(Bt,(N/partes)*i,partes);
        }
        //Obtenemos los hilos para  que trabajen en paralelo 
        Worker w[] = new Worker[2];
        w[0]=new Worker(r,N,M,a,b,c,18,1);
        w[1]=new Worker(r2,N,M,a,b,c,18,2);
        //Obtenemos C18 a C24 y obtenemos C25 a C81
        w[0].run();
        w[1].run();
        for(int i=0;i<partes*2;i++){
            if(i<partes){
                c[i]=multiplica_matrices(a[0], b[i], N, M);
            }
            else{
                c[i]=multiplica_matrices(a[1], b[i-9], N, M);
            }
        }
        //Esperamos respuesta
        w[0].join();
        w[1].join();
        //Juntamos C
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                acomoda_matriz(C, c[(i*9+j)], (i*N/9), (j*N/9), N);
            }
        }
        System.out.println();
        //Si N = 6 y M = 5 imprime C 
        if(N==9 && M==4){
            System.out.println("MATRIZ A");
            imprime_matriz(A, N, M);
            System.out.println();
            System.out.println("MATRIZ B");
            imprime_matriz(B, M, N);
            System.out.println();
            System.out.println("MATRIZ C");
            imprime_matriz(C, N, N);
            System.out.println();
            System.out.println("El checksum es: "+checksum(C, N, N));
        }
        else {
            System.out.println("El checksum es: "+checksum(C, N, N));
        }        
    }
}