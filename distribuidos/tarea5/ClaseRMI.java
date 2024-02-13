import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ClaseRMI extends UnicastRemoteObject implements InterfaceRMI{
    int partes=6;
    public ClaseRMI() throws RemoteException{
        super( );
    }
    public double[][] multiplica_matrices(double[][] A, double[][] B, int N,int M) {
        double [][] C = new double [N/9][N/9];
        for(int i=0;i<N/9;i++)
            for(int j=0;j<N/9;j++)
                for(int k=0;k<M;k++)
                    C[i][j] += A[i][k]*B[j][k];
        return C;
    }
}