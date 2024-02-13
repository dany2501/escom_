#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define ewe 512

int main(){
 int udp_socket, lbind, tam, tam2, lrecv;
 struct sockaddr_in local, remota;
 //unsigned char msj[100] = "Hola red soy Daniel";
 char messenger [50];
 char paqRec[ewe];
 udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 if(udp_socket == -1){
 	perror("\nError al abrir el socket");
 }
 
 else{
 	perror("\nExito al abrir el socket");
 	local.sin_family = AF_INET;
 	local.sin_port = htons(0);
 	local.sin_addr.s_addr = INADDR_ANY;
 	lbind = bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
 	if(lbind == -1){
 		perror("\nError en bind");
 		exit(0);
 	}
 	
 	else{
 		perror("\nExito en bind");
 		remota.sin_family = AF_INET;
 		remota.sin_port = htons(8080);
 		remota.sin_addr.s_addr = inet_addr("10.0.2.15");
 		//iniciar ciclo
 		do{
 			printf("\nMensaje: ");
 			fgets(messenger, ewe, stdin);
 			tam = sendto(udp_socket, messenger ,strlen(messenger) + 1, 0, (struct sockaddr *)&remota, sizeof(remota));
 			if(tam == -1){
 				perror("\nError al enviar");
 				exit(0);
 			}	
 			else{
 				perror("\nExito al enviar");
 				lrecv = sizeof(remota); 
 				tam2 = recvfrom(udp_socket, paqRec , 512, 0, (struct sockaddr *)&remota, &lrecv);
 				if(tam2 == -1){
 					perror("\nError al recibir");
 					exit(0);
 				}
 		
 				else{
 					printf("\nMensaje enviado: %s\n", paqRec);
 				}
 			}
 		}while(messenger != "Bye");
 		
 	}
 }
 
 close(udp_socket);
 return 0;
}

