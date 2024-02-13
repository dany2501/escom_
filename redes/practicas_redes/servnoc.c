#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define awa 512

int main(){
 int udp_socket, lbind, tam ,lrecv, tam2;
 struct sockaddr_in servidor, cliente;
 //unsigned char msj[100] = "Hola red soy Daniel";
 char messenger2[50];
 char paqRec[awa];
 udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 if(udp_socket == -1){
 	perror("\nError al abrir el socket");
 }
 
 else{
 	perror("\nExito al abrir el socket");
 	servidor.sin_family = AF_INET;
 	servidor.sin_port = htons(8080);
 	servidor.sin_addr.s_addr = INADDR_ANY;
 	lbind = bind(udp_socket, (struct sockaddr *)&servidor, sizeof(servidor));
 	if(lbind == -1){
 		perror("\nError en bind");
 		exit(0);
 	}
 	
 	else{
 		perror("\nExito en bind");
 		lrecv = sizeof(cliente); 
 		//inicio de bucle
 		do{
 			tam = recvfrom(udp_socket, paqRec , 512, 0, (struct sockaddr *)&cliente, &lrecv);
 			if(tam == -1){
 				perror("\nError al recibir");
 				exit(0);
 			}
 		
 			else{
 				printf("\nMensaje recibido: %s\n", paqRec);
 				printf("\nMensaje: ");
 				fgets(messenger2, awa, stdin);
 				tam2 = sendto(udp_socket, messenger2 ,strlen(messenger2) + 1, 0, (struct sockaddr *)&cliente, sizeof(cliente));
 				if(tam2 == -1){
 					perror("\nError al enviar");
 					exit(0);
 				}	
 				else{
 					perror("\nExito al enviar");
 				}
 		
 			}
 		 }while(messenger2 != "Bye");
 	}
 }
 close(udp_socket);
 return 0;
}

