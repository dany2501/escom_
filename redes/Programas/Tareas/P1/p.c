#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

unsigned char *IPdestino[4]={NULL};

int main(){
    FILE * archivo;
    
    long segs=2;
    char c=segs+'0';
    char *cad[3]={"23","234","35"}, nombre[]={"NOMBRE.txt"};

	archivo = fopen(nombre,"a");

    if(archivo==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }

    fputc('\n', archivo);

    for(int i=0;i<3;i++){
        fputs(cad[i], archivo);
        fputc(' ',archivo);
    }
    
    fputs("\nTiempo de respuesta: ", archivo);
    fputc(c, archivo);
    fputs("\n\n", archivo);

    fclose(archivo);
    return 1;
}