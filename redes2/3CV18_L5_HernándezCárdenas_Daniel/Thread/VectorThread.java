import java.util.*;
import java.lang.*;
public class VectorThread extends Thread{

    public VectorThread(String str){
        super(str);
    }


    public void run(){
        int c = getRandom();
        System.out.println("Vector "+getName() +" size "+ c);

        Vector<Number> v = new Vector<>(c);
        for(int i = 0;i<c;i++){
            v.addElement(getRandom());
        }
        
        System.out.println("suma "+getName()+" vector "+this.suma(v));
        System.out.println("suma cuadrados "+getName()+" vector "+this.sumaCuadrados(v));
        System.out.println("Promedio "+getName()+" vector "+this.avg(v)+"\n");
    }

    public static void main(String[] args){
        new VectorThread("Primero").start();
        new VectorThread("Segundo").start();
    }

    public static int getRandom(){
        Random r = new Random();
        int c = r.nextInt(1000);
        if (c>0){
            return c;
        }else{
            return c*-1;
        }
    }

    public static int suma(Vector<Number> v){

        int suma = 0;
        for (int j=0;j<v.size();j++){
            int aux = v.elementAt(j).intValue();
            suma += aux;
        }
        
        return suma;
    }

    public static int sumaCuadrados(Vector<Number> v){

        int suma = 0;
        for (int j=0;j<v.size();j++){
            int aux = v.elementAt(j).intValue();
            int n = aux*aux;
            suma += n;
        }
        
        return suma;
    }

    public static int avg(Vector<Number> v){

        int suma = 0;
        for (int j=0;j<v.size();j++){
            int aux = v.elementAt(j).intValue();
            suma += aux;
        }
        int average = suma / v.size();
        
        return average;
    }
    
}