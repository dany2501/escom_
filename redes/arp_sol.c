#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>

unsigned char MACorigen[6];
unsigned char mascara[4];
unsigned char ip[4];
unsigned char MACbroad[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char ethertype[2]={0x08,0x06};
unsigned char type_hardware[2]={0x00,0x01};
unsigned char type_protocol[2]={0x08,0x00};
unsigned char long_dir_hardw[2]={0x06,0x00};
unsigned char long_dir_prot[2]={0x04,0x00};
unsigned char code[2]={0x00,0x01};
unsigned char code_resp[2]={0x00,0x02};
unsigned char tha[6]={0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char tpa[4]={0xC0,0xA8,0x00,0x72}; //<----------Aqui pon tu ip bro en hexa
unsigned char tramaEnv[1514],tramaRec[1514];

int obtenerDatos(int ds){
    unsigned char nombre[20];
    int i,index;
    struct ifreq nic;
    printf("\nInserta el nombre de la interfaz: ");
    gets(nombre);
    strcpy(nic.ifr_name,nombre);
    if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
        perror("\nError al obtener el index");
        exit(0);
    }
    else{
        index=nic.ifr_ifindex;
        printf("\nEl indice es: %d",nic.ifr_ifindex);

        if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
            perror("\nError al obtener la MAC");
            exit(0);
        }
        else{
            memcpy(MACorigen,nic.ifr_hwaddr.sa_data,6);
            printf("\nLa MAC es: ");
            for(i=0;i<6;i++){
                printf("%.2x:",MACorigen[i]);
            }

            if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
                perror("\nError al obtener la mascara");
                exit(0);
            }
            else{
                memcpy(mascara,nic.ifr_netmask.sa_data+2,4);
                printf("\nLa mascara es: ");
                for(i=0;i<4;i++){
                    printf("%d:",mascara[i]);
                }

                if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
                    perror("\nError al obtener la ip");
                    exit(0);
                }
                else{
                    memcpy(ip,nic.ifr_addr.sa_data+2,4);
                    printf("\nLa ip es: ");
                    for(i=0;i<4;i++){
                        printf("%d:",ip[i]);
                    }
                }
            }
        }
    }
    return index;
}
void estructuraTrama(unsigned char *trama){

    memcpy(trama+0,MACbroad,6);
    memcpy(trama+6,MACorigen,6);
    memcpy(trama+12,ethertype,2);
    memcpy(trama+14,type_hardware,2);
    memcpy(trama+16,type_protocol,2);
    memcpy(trama+18,long_dir_hardw,2);
    memcpy(trama+19,long_dir_prot,2);
    memcpy(trama+20,code,2);
    memcpy(trama+22,MACorigen,6);
    memcpy(trama+28,ip,4);
    memcpy(trama+32,tha,6);
    memcpy(trama+38,tpa,4);

}
void enviarTrama(int ds,int index,unsigned char* trama){
    int tam;
    struct sockaddr_ll interfaz;
    memset(&interfaz,0x00,sizeof(interfaz));
    interfaz.sll_family=AF_PACKET;
    interfaz.sll_protocol=htons(ETH_P_ALL);
    interfaz.sll_ifindex=index;
    tam=sendto(ds,trama,60,0,(struct sockaddr*)&interfaz,sizeof(interfaz));
    if(tam<-1){
        perror("\nError al enviar");
        exit(0);
    }
    else perror("\nExito al enviar");
}
void imprimirTrama(unsigned char*paq,int len){
    int i;
    for(i=0;i<len;i++){
        if(i%16==0)
            printf("\n");
        printf("%.2x ",paq[i]);
    }
    printf("\n");
}
void recibirTrama(int ds, unsigned char *trama){
    int tam;
    while(1){
        tam=recvfrom(ds,trama,1514,0,NULL,0);
        if(tam==-1){
            perror("\nError al recibir");
            exit(0);
        }
        else {
            if(!memcmp(trama+0,MACorigen,6)&&!memcmp(trama+12,ethertype,2)&&!memcmp(trama+20,code_resp,2)){
                imprimirTrama(trama,tam);
                break;
            }
        }
    }
}
int main(){
    int packet_socket,indice;
    packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(packet_socket==-1){
        perror("\nError al abrir el socket");
        exit(0);
    }
    else{
        perror("\nExito al abrir el socket");
        indice=obtenerDatos(packet_socket);
        estructuraTrama(tramaEnv);
        imprimirTrama(tramaEnv,42);
        //printf("%s",tramaEnv);
        enviarTrama(packet_socket,indice,tramaEnv);
        recibirTrama(packet_socket,tramaRec);
    }
    close(packet_socket);
    return 0;
}
