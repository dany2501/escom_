public class Auto implements Serializable{
    private String nombre;
    private String imagen;
    private int precio;
    private int stock;

    public Auto (String nombre, String imagen, int precio, int stock){
        this.nombre = nombre;
        this.imagen = imagen;
        this.precio = precio;
        this.stock = stock;
    }

    public String getNombre(){
        return this.nombre;
    }

    public String getImagen(){
        return this.imagen;
    }

    public int getPrecio(){
        return this.precio;
    }

    public int getStock(){
        return this.stock;
    }

}