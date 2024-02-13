public class NumerosRunnable implements Runnable{


    public void run(){
        String type = Thread.currentThread().getName();
        System.out.println("Empieza "+type);
        for(int i=1;i<=10;i++){
            if (type.equals( "Par" ) && i%2==0){
                System.out.println(i);
            }else if (type.equals( "Impar" )  && i%2==1){
                System.out.println(i);
            }
                
        }
        System.out.println("Termina thread "+Thread.currentThread().getName());
    }
    
    public static void main(String[] args){

        new Thread(new NumerosRunnable(),"Par").start();
        new Thread(new NumerosRunnable(),"Impar").start();
        
        System.out.println("Termina thread main");
    }

}