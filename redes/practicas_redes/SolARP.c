#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
unsigned char MACOrigen[6];
unsigned char MACDestino[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char IPOrigen[4];
unsigned char IPDestino[4];
unsigned char mascaraRed[4];
unsigned char broad[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
unsigned char ethertype[2] = {0x08, 0x06};
unsigned char ethernet[2] = {0x00, 0x01};
unsigned char protocolo[2] = {0x08, 0x00};
unsigned char longitud[2] = {0x06, 0x04};
unsigned char codigo[2] = {0x00, 0x01};
unsigned char codresp[2] ={0x00, 0x02};

int obtenerDatos(int ds){
	struct ifreq nic;
    	unsigned char interface[20];
    	int i, index;
    	printf("\nInserta el nombre de la interfaz: ");
    	gets(interface);
    	strcpy(nic.ifr_name, interface);
    	if (ioctl(ds, SIOCGIFINDEX, &nic) == -1)
    	{
        	perror("\n Error al obtener el index");
        	exit(0);
    	}
    	else
    	{
        	index = nic.ifr_ifindex;
        	printf("\n>>El indice es: %d \n", index);
        	if (ioctl(ds, SIOCGIFHWADDR, &nic) == -1){
            		perror("\n Error al obtener la MAC");
            		exit(0);
        	}
        	else{
            		memcpy(MACOrigen, nic.ifr_hwaddr.sa_data, 6);
            		printf("\n>>La MAC es: ");
            		for (i = 0; i < 6; i++){
                		printf("%.2x:", MACOrigen[i]);
            		}
            		printf("\n");
        	}
        		if (ioctl(ds, SIOCGIFNETMASK, &nic) == -1){
            			perror("Error al obtener la Máscara de subred");
            			exit(0);
        		}
        			else{
            				memcpy(mascaraRed, nic.ifr_netmask.sa_data + 2, 4);
            				printf("\n>>La Mascara de Subred es: ");
            				for (int i = 0; i < 4; i++){
                				printf("%d.", mascaraRed[i]);
            				}
            				printf("\n");
        			}
        			if (ioctl(ds, SIOCGIFADDR, &nic) == -1){
            				perror("Error al obtener la direccion ip");
            				exit(0);
        			}
        				else{
            					memcpy(IPOrigen, nic.ifr_addr.sa_data + 2, 4);
           					printf("\n>>La direccion IP es: ");
            					for (int i = 0; i < 4; i++){
                					printf("%d.", IPOrigen[i]);
            					}
            			
        				}
    }
    return index;
}

void obtenIPD(){
    unsigned char destiny[16];
    printf("\n>>Ingresa la direccion IP de destino: ");
    gets(destiny);
    struct sockaddr_in ip;
    inet_aton(destiny,&ip.sin_addr);
    memcpy(IPDestino,&ip.sin_addr,4);
}


void estructuraSolArp(unsigned char *trama){
    memcpy(trama + 0, broad, 6);
    memcpy(trama + 6, MACOrigen, 6);
    memcpy(trama + 12, ethertype, 2);
    memcpy(trama + 14, ethernet, 2);
    memcpy(trama + 16, protocolo, 2);
    memcpy(trama + 18, longitud, 2);
    memcpy(trama + 20, codigo, 2);
    memcpy(trama + 22, MACOrigen, 6);
    memcpy(trama + 28, IPOrigen, 4);
    memset(trama + 32, 0x00, 6);
    memcpy(trama + 38, IPDestino, 4);
}

int filtroARP(unsigned char *paq,int len){
    	if(!memcmp(paq,MACOrigen,6)){
        	if(!memcmp(paq+12,ethertype,2)){
           	 	if(!memcmp(paq+20,codresp,2)){
                		if(!memcmp(paq+28,IPDestino,4)){
                    			return 1;
                		}
            		}
        	}
    	}
    	else{
        	return 0;
    	}
}


void enviarTrama(int ds, int index, unsigned char *trama){
	int tam;
    	struct sockaddr_ll interfaz;
    	memset(&interfaz, 0x00, sizeof(interfaz));
    	interfaz.sll_family = AF_PACKET;
    	interfaz.sll_protocol = htons(ETH_P_ALL);
    	interfaz.sll_ifindex = index;
    	tam = sendto(ds, trama, 60, 0, (struct sockaddr *)&interfaz, sizeof(interfaz));
    	if (tam == -1){
        	perror("\nError al enviar la trama");
        	exit(0);
    	}
    	else{
        	perror("\nExito al enviar trama");
    	}
}


void imprimirTrama(unsigned char *paq, int len){
	int i;
    	for (i = 0; i < len; i++){
        	if (i % 16 == 0){
            		printf("\n");
        	}
        	printf("%.2x ", paq[i]);
    	}
}

void recibeRespArp(int ds, unsigned char *trama){
    int tam,control = 0;
    while (1){
        tam = recvfrom(ds, trama, 1514, 0, NULL, 0);
        if (tam == -1){
            perror("\nErrror al recibir trama");
            exit(0);
        }
        else{
            control=filtroARP(trama,tam);
            if(control == 1){
            	 printf("\n*******La trama que se recibe es*******\n");
                imprimirTrama(trama, tam);
                memcpy(MACDestino, trama + 22, 6);
                printf("\n>>La Mac de destino es: ");
                imprimirTrama(MACDestino,6);
                break;
            }
        }
    }
}

int main(){
    	unsigned char tramaEnv[1514],tramaRec[1514];
    	int packet_socket, indice, i;
    	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    	if (packet_socket == -1){
        	perror("\n Error al abrir el socket");
    	}
    	else{
        	perror("\nExito al abrir el socket");
        	indice = obtenerDatos(packet_socket);
        	obtenIPD();
        	estructuraSolArp(tramaEnv);
        	printf("\n********La trama que se envia es*******\n");
        	imprimirTrama(tramaEnv, 60);
        	printf("\n");
        	enviarTrama(packet_socket, indice, tramaEnv);
        	recibeRespArp(packet_socket,tramaRec);
        	printf("\n\n");
    }
    close(packet_socket);
    return 0;
}
