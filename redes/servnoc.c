#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <arpa/inet.h>
#include <string.h>



int main(int argc, char const *argv[])
{
	int udp_socket, lbind, tam, lrecv;
	struct sockaddr_in SERVIDOR, CLIENTE;
	unsigned char msj[512];
	unsigned char paqRec[512];
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udp_socket == -1)
	{
		perror("\nError al abrir el socket");
		exit(0); 
	}
	else
	{
		perror("\nExito al abrir el socket");
		SERVIDOR.sin_family = AF_INET; /* address family: AF_INET */
        SERVIDOR.sin_port = htons(8080);   /* port in network byte order */
        SERVIDOR.sin_addr.s_addr = INADDR_ANY;   /* internet address */
		lbind = bind(udp_socket, (struct sockaddr *) &SERVIDOR, sizeof(SERVIDOR));
		if(lbind == -1)
		{
			perror("\nError en bind");
			exit(0);
		}
		else
		{
			perror("\nExito en bind");
			lrecv = sizeof(CLIENTE);
			//inicio de ciclo
			while(1)
			{
				tam = recvfrom(udp_socket, paqRec, 512, 0, (struct sockaddr *)&CLIENTE, &lrecv);
	        	if(tam == -1)
	        	{
	        		perror("\nError al recibir");
	        		exit(0);
	        	}
	        	else
	        	{
	        		printf("\nEl mensaje Recibido es: %s\n",paqRec);
	        		//Solicito al usuario el mensaje a enviar
	        		//Envio el mensaje
	        		printf("Mensaje: ");
	        		fflush(stdin);
	        		fgets(msj, 512, stdin);
	        		puts("\n");
		        	tam = sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *) &CLIENTE, sizeof(CLIENTE));
		        	if(tam == -1)
		        	{
		        		perror("\nError al enviar");
		        		exit(0);
		        	}
		        	else
		        	{
		        		perror("\nExito al enviar");
		        	}
	        	}	
			}      	
        	
		}
	}
	close(udp_socket);
	return 0;
}       
       
       

