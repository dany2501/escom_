#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char DirecMACDest[12]={0}, DirecMACOrg[12]={0}, EthertypeAux[4]={0}, DSAP[2]={0}, SSAP[2]={0}, ControlAux[4]={0}, Control1[8]={0}, Control2[8]={0}, ConA1[8]={0}, ConA2[8]={0};
int Ethertype;

FILE * archivo;
FILE * Nv_arch;

void leeEscT();
int potencia(int a, int b);
void tablaProtocolo(char a, char b);
int hexa(char caracter, int b);
int bin (int a);

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("\n\nSe requiere el nombre del archivo txt de tramas y el nombre del nuevo txt\n\n");
        exit(0);
    }

    archivo = fopen(argv[1],"r");
    Nv_arch = fopen(argv[2],"w");

    if (archivo==NULL || Nv_arch==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }
    
    leeEscT();

    fclose(archivo);
    fclose(Nv_arch);
    return 0;
}

void leeEscT(){
    int c=0, i=0, j=3, k=1, l=1, v1=0, v2=0, v3=0;
    char caracter1=0, caracter2=0;
    printf("\n\t\tTRAMAS\n\n");

    fflush(stdin);
    fflush(stdout);

    while((caracter1 = fgetc(archivo)) != EOF){
        printf("%c", caracter1);
        if(caracter1 == '\n' && caracter2 == '\n'){
            printf("\nEntro a tramas1.txt\n");
            printf("SubCapa MAC\nDireccion MAC destino:\t%s\nDireccion MAC Origen:\t%s",DirecMACDest,DirecMACOrg);
            printf("\nLongitud:\t%s\t=\t%d\n\tSubCapa LLC\nDSAP:\t0x%s",EthertypeAux,Ethertype,DSAP);
            
            if(DSAP[1]=='0')
                printf("\t11110000\tIndividual\t-\t");
            else
                printf("\t11110001\tGrupo\t-\t");
            
            tablaProtocolo(DSAP[0], DSAP[1]);
            printf("SSAP:\t0x%s",SSAP);

            if(SSAP[1]=='0')
                printf("\t11110000\nComando\t");
            else
                printf("\t11110001\tRespuesta\t");
            
            tablaProtocolo(SSAP[0],SSAP[1]);
            printf("Control:\t0x%s\t",ControlAux);

            for(i=0; i<7; i++)
                printf("%c",Control1[i]);

            printf(" %c\t",Control1[7]);

            for(i=0; i<7; i++)
                printf("%c",Control2[i]);
            printf(" %c",Control2[7]);
            v3=0;

            for(i=6, j=0; 0<=i; i--, j++){
                if(Control1[i]==1)
                    v2 += potencia(2,j);
                if(Control1[i]==1)
                    v3 += potencia(2,j);
            }

            printf("\n\t\t\tN(S) = %i",v2);

            if(Control1[7] == 0)
                printf("\t Informacion\tN(R) = %i",v3);
            else
                printf("\t Otro\tN(R) = %i",v3);

            if(Control2[7] == 0)
                printf("\t P/F = \t%c\n\n\n",Control2[7]);
            else
                printf("\t P/F = \t%c\n\n\n",Control2[7]);

            c=0, i=0, j=3, k=1, l=1, v1=0, v2=0, v3=0;
        }else
            if(caracter1 != ' ' && caracter1 != '\n'){
                if(c<17){
                    DirecMACDest[i]=caracter1;
                    i++;
                }else if(17<c<35){
                    DirecMACOrg[i]=caracter1;
                    i++;
                }else if(35<c<41){               //Ethertype 00x0000
                    EthertypeAux[i]=caracter1;
                    v1 += hexa(caracter1, j);
                    Ethertype=v1;
                    i++;
                    j--;
                }else if(41<c<44){                      //DSAP 0x00
                    DSAP[i]=caracter1;
                    i++;
                }else if(44<c<47){                        //SSAP 0x00
                    SSAP[i]=caracter1;
                    i++;
                }else if(48<c<51){
                    ControlAux[i]=caracter1;
                    v2 += hexa(caracter2, k);
                    i++;
                    k--;
                }else if(51<c<54){
                    ControlAux[i]=caracter1;
                    v3 += hexa(caracter2, l);
                    i++;
                    l--;
                }
            }else if(c==17 || c==35 || c==41 || c==44 || c==48 || c==51)
                    i==0;
                else if(c==54){
                    i = bin(v2);

                    for(j=(8-i); j<8; j++)
                        Control1[j]==ConA1[7-j];

                    i = bin(v2);

                    for(j=(8-i); j<8; j++)
                        Control2[j]==ConA2[8-j];
                }else
                    printf("Hola xd\n");
        caracter2=caracter1;
        c++;
    }
}

void tablaProtocolo(char a, char b){
    if(a=='0' && b=='0')
        printf("Null LSAP");
    if(a=='0' && b=='2')
        printf("Individual LLC SUBlayer Management Function");
    if(a=='0' && b=='3')
        printf("Group LLC Sublayer Management Function");
    if(a=='0' && b=='4')
        printf("IBM SNA Path Control (individual)");
    if(a=='0' && b=='5')
        printf("IBM SNA Path Control (group)");
    if(a=='0' && b=='6')
        printf("ARPANET Internet Protocol (IP)");
    if(a=='0' && b=='E')
        printf("PROWAY (IEC955) Network Management & Initialization");
    if(a=='0' && (b=='8' || b=='C'))
        printf("SNA");
    
    if(a=='F' && b=='0')
        printf("IBM NetBIOS");
    if(a=='F' && b=='4')
        printf("IBM LAN Management (Individual)");
    if(a=='F' && b=='5')
        printf("IBM LAN Management (Group)");
    if(a=='F' && b=='8')
        printf("IBM Remote Program Load (RPL)");
    if(a=='F' && b=='A')
        printf("Ungermann-Bass");
    if(a=='F' && b=='E')
        printf("ISO Network Layer Protocol");
    if(a=='F' && b=='F')
        printf("Global LSAP");
    
    if(a=='8' && b=='0')
        printf("Xerox Netwoork Systems (XNS)");
    if(a=='8' && b=='6')
        printf("Nestar");
    if(a=='8' && b=='E')
        printf("PROWAY (IEC 955) Active Station List Maintenance");
    
    if(a=='4' && b=='2')
        printf("IEEE 802.1 Bridge Spanning Tree Protocol");
    if(a=='4' && b=='E')
        printf("EIA RS-511 Manofacturing Message Service");
    
    if(a=='1' && b=='8')
        printf("Texas Instruments");
    if(a=='9' && b=='8')
        printf("ARPANET Address Resolution Protocol (ARP)");
    
    if(a=='7' && b=='E')
        printf("ISO 8280 (X.25 over IEEE 802.2 Type 2 LLC)");
    if(a=='B' && b=='C')
        printf("Banyan VINES");
    if(a=='A' && b=='A')
        printf("SubNetwork Access Protocol (SNAP)");
    if(a=='E' && b=='0')
        printf("Novell NetWare");
}

int hexa(char caracter1, int b){
    if('0'<=caracter1<='9'){
        int c=caracter1 - '0';
        return c*potencia(16,b);
    }else{
        if(caracter1=='a')
            return 10*potencia(16,b);
        else if(caracter1=='b')
            return 11*potencia(16,b);
        else if(caracter1=='c')
            return 12*potencia(16,b);
        else if(caracter1=='d')
            return 13*potencia(16,b);
        else if(caracter1=='e')
            return 14*potencia(16,b);
        else if(caracter1=='f')
            return 15*potencia(16,b);
        else{
            printf("\nError en Ethertype\n");
            exit(0);
        }
    }
}

int bin(int a){
    int i=0;

    while(a != 0 && a != 1){
        ConA1[i]=a%2;
        a = a/2;
        i++;
    }

    return i;
}

int potencia(int a, int b){
    int c=a;

    for(int i=1; i<b; i++)
        c*=a;

    return c;
}