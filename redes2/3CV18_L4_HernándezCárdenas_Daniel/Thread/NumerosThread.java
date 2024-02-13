public class NumerosThread extends Thread{

    public NumerosThread(String str){
        super(str);
    }


    public void run(){

        String type = getName();
        System.out.println("Empieza "+type);

        for(int i=1;i<=10;i++){
            if (type.equals( "Par" ) && i%2==0){
                System.out.println(i);
            }else if (type.equals( "Impar" )  && i%2==1){
                System.out.println(i);
            }
                
        }
        System.out.println("Termina thread "+getName());
    }

    public static void main(String[] args){

        new NumerosThread("Par").start();
        new NumerosThread("Impar").start();
        
        System.out.println("Termina thread main");
    }
    
}