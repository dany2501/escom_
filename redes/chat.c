#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int udp_socket,lbind,tamaño;
    struct sockaddr_in local,remota;
    unsigned char msj[100]="Hola red";
    udp_socket=socket(AF_INET,SOCK_DGRAM,0);

    if(udp_socket==-1){
        perror("Error al abrir el socket");
        exit(0);
    }
    else{
        perror("Exito al abrir el socket");
        local.sin_family=AF_INET;
        local.sin_port=htons(0);
        local.sin_addr.s_addr=INADDR_ANY;
        lbind=bind(udp_socket,(struct sockaddr * )&local,sizeof(local));
        if(lbind==-1){
            perror("Error en bind");
            exit(0);
        }else{
            perror("Exito en bind");
            remota.sin_family=AF_INET;
            remota.sin_port=htons(8080);
            remota.sin_addr.s_addr=inet_addr("192.168.0.114");
            tamaño=sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *)&remota,sizeof(remota));
            if(tamaño==-1){
                perror("Error al enviar");
                exit(0);
            }else{
                perror("Exito al enviar");
            }
        }
    }
    close(udp_socket);
    return 0;
}