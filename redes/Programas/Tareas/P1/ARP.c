#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/ethernet.h> 
#include <linux/if_packet.h>

unsigned char IPorigen[4];
unsigned char *IPdestino[4]={NULL};
unsigned char MACorigen[6];
unsigned char MACdestino[6];
unsigned char MASKsubred[4];
unsigned char tramaARPresp[1514];
unsigned char etherARP[2]={0x08,0x06};
unsigned char codARPresp[2]={0x00,0x02};
unsigned char tramaARPsol[60]={0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x06,0x00,0x01,
							0x08,0x00,0x06,0x04,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,'G','S','Q'};

int obtenDatos(int ds){
	struct ifreq nic;
	int i=0, index;
	char cad[15], nombre[50];

	printf("\nInserta nombre de Red: ");
	scanf("%s",nombre);
	strcpy(nic.ifr_name, nombre);

	printf("Ingresar la IP: ");
	scanf("%hhd.%hhd.%hhd.%hhd",IPdestino,IPdestino+1,IPdestino+2,IPdestino+3);

/*	scanf("%s",cad);

    if((IPdestino[0] = strtok(cad, ".")) != NULL)
        do
            i++;
        while((IPdestino[i] = strtok(NULL, ".")) != NULL && i<4);
*/
	if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
		perror("\n\nError en el indice");
		exit(0);
	}else{
		index=nic.ifr_ifindex;
		printf("\n\nExito al obtener el índice: %d", index);

		if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
			perror("\n\nError al obtener la MAC");
			exit(0);
		}else{
			memcpy(MACorigen, nic.ifr_hwaddr.sa_data,6);
			printf("\nLa MAC es: ");
			
			for(i=0;i<6;i++)
				printf("%.2x:", MACorigen[i]);

			printf("\nEl tipo hardware de ARP es: %.4X", nic.ifr_hwaddr.sa_family);

			if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
					perror("\nError al obtener el IP");
					exit(0);
			}else{
				memcpy(IPorigen, nic.ifr_addr.sa_data + 2, 4);
				printf("\nLa IP es: ");
			
				for(i=0;i<4;i++)
					printf("%d.", IPorigen[i]);
				
				printf("\nFamilia: %.4X", nic.ifr_addr.sa_family);

				if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
						perror("\nError al obtener la MASK");
						exit(0);
				}else{
					perror("Exito al obtener la MASK");
					memcpy(MASKsubred, nic.ifr_netmask.sa_data + 2, 4);
					printf("\nLa MASK es: ");
			
					for(i=0;i<4;i++)
						printf("%d.", MASKsubred[i]);
					
					printf("\nFamilia: %.4x\n",nic.ifr_netmask.sa_family);
				}
			}
		}
	
		return index;
	}
}

void estructuraARPsol(unsigned char *trama){
	memcpy(trama+6,MACorigen,6);
	memcpy(trama+22,MACorigen,6);
	memcpy(trama+28,IPorigen,4);
	memset(trama+32,0x00,6);
	memcpy(trama+38,IPdestino,4);
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

void recibeARPresp(int ds, unsigned char *trama){
	int tam;

	while(1){
		tam=recvfrom(ds,trama,1514,0,NULL,0);

		if(tam==-1){
			perror("Error al recibir");
			exit(1);
		}else
			if(!memcmp(trama+0,MACorigen,6)||!memcmp(trama+6,MACorigen,6))
				break;
	}
}

void impTrama(unsigned char *paq, int len){
	int i;
	for(i=0;i<len;i++){
		if(i%16==0){
			printf("\n");
		}
		printf("%.2x ",paq[i]);
	}
	printf("\n\n");
}

int main(){
	int packet_socket;
	int in;
	
	packet_socket=socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if(packet_socket==-1){ 
		perror("\nError al abrir el socket");
	    exit(1);
	}else
		perror("\nExito al abrir el socket");

	in = obtenDatos(packet_socket);
	
	estructuraARPsol(tramaARPsol);
	printf("\nTrama enviada");
	enviaTrama(packet_socket, in, tramaARPsol);
	recibeARPresp(packet_socket, tramaARPresp);
	printf("\n\n\t\tTrama recibida\n");
	impTrama(tramaARPresp,60);
	
	close(packet_socket);

	return 1;
}