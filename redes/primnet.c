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
	struct sockaddr_in local, remota;
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
		local.sin_family = AF_INET; /* address family: AF_INET */
        local.sin_port = htons(0);   /* port in network byte order */
        local.sin_addr.s_addr = INADDR_ANY;   /* internet address */
		lbind = bind(udp_socket, (struct sockaddr *) &local, sizeof(local));
		if(lbind == -1)
		{
			perror("\nError en bind");
			exit(0);
		}
		else
		{
			perror("\nExito en bind");
			remota.sin_family = AF_INET; /* address family: AF_INET */
        	remota.sin_port = htons(8080);   /* port in network byte order */
        	remota.sin_addr.s_addr = inet_addr("192.168.0.114");   /* internet address */
        	//Iniciar ciclo
        	while(1)
        	{
        		//capturar el mensaje
        		printf("Mensaje: ");
        		fflush(stdin);
        		fgets(msj, 512, stdin);
        		puts("\n");
	        	tam = sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *) &remota, sizeof(remota));
	        	if(tam == -1)
	        	{
	        		perror("\nError al enviar");
	        		exit(0);
	        	}
	        	else
	        	{
	        		perror("\nExito al enviar");
	        		//Pongo a recibir el mensaje de respuesta
	        		//Imprimo el mensaje
	        		lrecv = sizeof(remota);
		        	tam = recvfrom(udp_socket, paqRec, 512, 0, (struct sockaddr *)&remota, &lrecv);
		        	if(tam == -1)
		        	{
		        		perror("\nError al recibir");
		        		exit(0);
		        	}
		        	else
		        	{
		        		printf("\nEl mensaje recibido es: %s\n",paqRec);
		        	}

	        	}
        	}
		}
	}
	close(udp_socket);
	return 0;
}       
       
       

