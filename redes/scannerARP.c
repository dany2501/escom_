#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h>
#include <net/if.h>
#include <string.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>

int numero=0;

unsigned char IPorigen[4];
unsigned char IPdestino[4];
unsigned char MACorigen[6];
unsigned char MACdestino[6];
unsigned char MASKsubred[4];
unsigned char tramaARPresp[1514];
unsigned char etherARP[2]={0x08,0x06};
unsigned char codARPresp[2]={0x00,0x02};
unsigned char tramaARPsol[42]={ 0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
								0x00,0x00,0x08,0x06,0x00,0x01,0x08,0x00,0x06,0x04,
								0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								0x00,0x00};

void impTrama(unsigned char *paq, long segs){
	int i;

	for(i=0;i<42;i++){
		if(i%16==0)
			printf("\n");
		printf("%.2x ",paq[i]);
	}

	printf("\nTiempo de respuesta ===> %ld segundos",segs);
}

int obtenDatos(int ds){
	struct ifreq nic;
	int i, index;
	char cad[15],nombre[50],*token[]={NULL};

	printf("\nInserta nombre de Red: ");
	scanf("%s",nombre);
	strcpy(nic.ifr_name, nombre);

	printf("Ingresar la IP: ");
	scanf("%hhd.%hhd.%hhd.%hhd",IPdestino,IPdestino+1,IPdestino+2,IPdestino+3);

	if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
		perror("\nError en el indice");
		exit(0);
	}else{
		index=nic.ifr_ifindex;
		printf("\nExito al obtener el índice: %d", index);

		if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
			perror("\nError al obtener la MAC");
			exit(0);
		}else{
			memcpy(MACorigen, nic.ifr_hwaddr.sa_data,6);
			printf("\nLa MAC es ==> ");
			
			for(i=0;i<6;i++)
				printf("%.2x:", MACorigen[i]);

			if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
					perror("\nError al obtener el IP");
					exit(0);
			}else{
				memcpy(IPorigen, nic.ifr_addr.sa_data + 2, 4);
				printf("\nLa IP es: ");
			
				for(i=0;i<4;i++)
					printf("%d.", IPorigen[i]);
				
				printf("\nFamilia: %.4X\n", nic.ifr_addr.sa_family);

				if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
						perror("\nError al obtener la mascara de subred");
						exit(0);
				}else{
					perror("Exito al obtener la mascara de subred");
					memcpy(MASKsubred, nic.ifr_netmask.sa_data + 2, 4);
					printf("\nLa mascara de subred es: ");
			
					for(i=0;i<4;i++)
						printf("%d.", MASKsubred[i]);
					
					//printf("\nFamilia: %.4x\n\n",nic.ifr_netmask.sa_family);
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

	printf("\n\n---------Se envio la trama----------");
	struct sockaddr_ll capaEnlace;

	memset(&capaEnlace, 0x00, sizeof(capaEnlace));
	capaEnlace.sll_family = AF_PACKET;
	capaEnlace.sll_protocol=htons(ETH_P_ALL);
	capaEnlace.sll_ifindex=index;
	tam = sendto(ds,paq,42,0,(struct sockaddr*)&capaEnlace,sizeof(capaEnlace));
	
	if(tam==-1)
		perror("\nError al enviar la trama");
	else{
		numero++;
		printf("\nSe recibio la trama => %d",numero);
	}
}

int filtroARP(unsigned char *paq){
	if (!memcmp(paq ,MACorigen, 6))
		if (!memcmp(paq + 12, etherARP, 2))
			if (!memcmp(paq + 28, IPdestino, 4))
				if (!memcmp(paq + 38, IPorigen, 4))
					return 1;
	return 0;
}

void guardar(unsigned char *paq, long segs, char nombre[]){
	FILE * archivo;
	archivo = fopen(nombre,"a");
   
    if(archivo==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }
	
	fprintf(archivo,"\n\t¡La trama numero => %i respondio!\n", numero);

	for (int i=0; i<42; i++){
		if(i%16==0)
			fputc('\n',archivo);
		if(i==5){
			fputs("Dirección MAC => ",archivo);
		}
		if(i>=6 && i<12){
			fprintf(archivo,"%.2x ", tramaARPresp[i]);
		}
		if(i==27){
			fputs("\nDirección IP => ",archivo);
		}

		if(i>=28 && i<32){
			fprintf(archivo,"%.2x ", tramaARPresp[i]);
		}
	}
	
	fprintf(archivo,"\n\nTiempo de respuesta ====> %ld segundos\n\n", segs);
	fclose(archivo);
}

void recibeARPresp(int ds, unsigned char *trama, char nombre[]){
	int tam,bandera = 0;
	struct timeval inicio, final;
	long tiempo = 0, seconds, useconds;

	gettimeofday(&inicio, NULL);
  
	while (tiempo < 200){
    	tam = recvfrom(ds,trama,1514,0,NULL,0);
    	
		if (tam == -1)
    		perror("\nError al recibir la trama");
	    else{
			gettimeofday(&final, NULL);
	
			seconds = final.tv_sec - inicio.tv_sec;
			useconds = final.tv_usec - inicio.tv_usec;
			tiempo = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		
			if ((bandera=filtroARP(trama)) == 1){
				printf("\n\n\t\tTrama recibida\n");
				impTrama(tramaARPresp,tiempo);
				guardar(tramaARPresp,tiempo,nombre);
				break;
			}
  		}
	}
}

int main(int argc, char *argv[]){
	int in,packet_socket;
	if(argc != 2){
        printf("\nAgrega un nombre para el archivo de respuestas\n\n");
        exit(0);
    }

	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if(packet_socket == -1){ 
		perror("\nError al abrir el socket");
	    exit(1);
	}else
		perror("\nExito al abrir el socket");

	in = obtenDatos(packet_socket);

	estructuraARPsol(tramaARPsol);
	
	for(int i=0; i<255; i++){
		tramaARPsol[41]=i;
		IPdestino[3]=i;
		enviaTrama(packet_socket, in, tramaARPsol);
		recibeARPresp(packet_socket, tramaARPresp, argv[1]);
	}
	
	close(packet_socket);
	printf("\n");

	return 1;
}
