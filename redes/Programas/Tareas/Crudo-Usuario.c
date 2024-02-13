#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <linux/if_packet.h> 
#include <net/ethernet.h> 
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <net/if_arp.h>

unsigned char IP[20];
unsigned char IPorigen[4];
unsigned char MACorigen[6];
unsigned char IPdestino[4];
unsigned char MASKsubred[4];
unsigned char tramaARPresp[1514];
unsigned char ethertype[2]={0x0c,0x0c};
unsigned char codARPresp[2]={0x00,0x02};
unsigned char etherARP[2]={0x00,0x01};
unsigned char MACbroadcast[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char tramaARPsol[60]={0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x06,0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,'G','S','Q'};

unsigned char tramaEnv[1514];
unsigned char tramaRec[1514];

unsigned char mensaje[60];

/*void estructuraTrama(unsigned char *trama){
	memcpy(trama+0,MACbroadcast,6);
	memcpy(trama+6,MACorigen,6);
	memcpy(trama+12,ethertype,2);
	memcpy(trama+14,"Escobar",10);
}*/

/*void enviarTrama(int ds, int indice, unsigned char *trama){
	struct sockaddr_ll nic;
	int tam;
	memset(&nic,0x00,sizeof(nic));
	nic.sll_family=AF_PACKET;
	nic.sll_protocol=htons(ETH_P_ALL);
	nic.sll_ifindex=indice;
	tam=sendto(ds,trama,60,0,(struct sockaddr *)&nic,sizeof(nic));
	
	if(tam==-1){
		perror("Error al enviar");
		exit(1);
	}else{
		perror("Exito al enviar");
		exit(0);
	}
}*/

/*int obtenDatos(int ds){
  struct ifreq nic;
  int i, index;
  char nombre[50];
  printf("\nInserta nombre:");
  scanf("%s",nombre);
  strcpy(nic.ifr_name, nombre);

  if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
    perror("\nError en el indice");
    exit(0);
  }else{
	perror("Exito al obtener el índice");
	index=nic.ifr_ifindex;

	if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
	    perror("\nError al obtener la MAC");
	    exit(0);
	}else{
		perror("Exito al obtener la MAC");
		memcpy(MACorigen, nic.ifr_hwaddr.sa_data,6);
		printf("La MAC es: ");
		
		for(i=0;i<6;i++)
			printf("%.2x:", MACorigen[i]);

		if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
	    		perror("\nError al obtener el IP");
	    		exit(0);
		}else{
			perror("Exito al obtener el IP");
			memcpy(IPorigen, nic.ifr_addr.sa_data + 2, 4);
			printf("\nLa IP es: ");
		
			for(i=0;i<4;i++)
				printf("%d.", IPorigen[i]);

			if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
		    		perror("\nError al obtener la MASK");
		    		exit(0);
			}else{
				perror("Exito al obtener la MASK");
				memcpy(MASKsubred, nic.ifr_netmask.sa_data + 2, 4);
				printf("\nLa MASK es: ");
		
				for(i=0;i<4;i++)
					printf("%d.", MASKsubred[i]);
				
				printf("\n\n");
  			}
		}
  	}
    return index;
  }
}*/


void impTrama(unsigned char *paq, int len){
	int i;
	for(i=0;i<len;i++){
		if(i%16==0){
			printf("\n");
		}
		printf("%.2x",paq[i]);
	}
	printf("\n\n");
}

void recTrama(int ds, unsigned char *trama){
	int tam;
	while(1){
		tam=recvfrom(ds,trama,1514,0,NULL,0);
		if(tam==-1){
			perror("Error al recibir");
			exit(1);
		}else{
			if(!memcmp(trama+0,MACorigen,6)||!memcmp(trama+6,MACorigen,6)){
				impTrama(trama,tam);
				printf("\n\n");
			}
		}
	}
}

int filtroARP(unsigned char *paq,int len){
	if(!memcmp(paq,MACorigen,6)){
		if(!memcmp(paq+12,etherARP,2))
			if(!memcmp(paq+20,codARPresp,2))
				if(!memcmp(paq+38,IPorigen,4))
					return 1;
	}else
		return 0;
}

void recibeARPresp(int ds,unsigned char *trama){
	int tam,bandera=0;

	while(1){
		tam=recvfrom(ds,trama,1514,0,NULL,0);
		
		if(tam==-1)
			perror("\nError al recibir");
		else{
			bandera=filtroARP(trama,tam);
			
			if(bandera==1)
				break;
		}
	}
}

void enviaTrama(int ds,int index,unsigned char *paq){
	
	int tam;
	struct sockaddr_ll capaEnlace;

	memset(&capaEnlace, 0x00, sizeof(capaEnlace));
	capaEnlace.sll_family = AF_PACKET;
	capaEnlace.sll_protocol=htons(ETH_P_ALL);
	capaEnlace.sll_ifindex=index;
	tam = sendto(ds,paq,60,0,(struct sockaddr*)&capaEnlace,sizeof(capaEnlace));
	
	if(tam==-1)
		perror("\nError al enviar la trama");
	else
		perror("\nExito al enviar la trama");
}

int estructuraARPsol(unsigned char *trama){
	memcpy(trama+6,MACorigen,6); //Encabezado
	memcpy(trama+22,MACorigen,6); //ARP
	memcpy(trama+28,IPorigen,4);
	memset(trama+32,0x00,6);
	memcpy(trama+38,IPdestino,4);
}

void pideDatos(){

	printf("\nIntroduzca la IP destino: ");
	gets(IP);
	inet_aton(IP,IPdestino);

	printf("\nIntroduzca mensaje: ");
	gets(mensaje);
	inet_aton(mensaje,tramaEnv);

}

int main(){

	int packet_socket;
	int indice, in;
	
	packet_socket=socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	pideDatos();
	
	if(packet_socket==-1){ 
		perror("\nError al abrir el socket");
	    exit(1);
	}else{
		perror("\nExito al abrir el socket");
		indice=obtenDatos(packet_socket);
		recibeARPresp(packet_socket, tramaARPsol);
		estructuraARPsol(tramaARPsol);

		//estructuraTrama(tramaEnv);
		//enviarTrama(packet_socket,indice,tramaEnv);
		//recTrama(packet_socket,tramaRec);
		//printf("\nEl indice es: %d \n",indice);

		impTrama(tramaARPresp,60);
	}
	close(packet_socket);
	printf("\n");
return 1;
}
/*Estudiar para mañana Protocolo ARP*/