#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char DirecMACDest[12], DirecMACOrg[12], EthertypeAux[4], DSAP[2], SSAP[2], ControlAux[4], Control1[8], Control2[8], ConA[8];
int Ethertype;

FILE * archivo;
FILE * Nv_arch;

void leeEscT();
int potencia(int a, int b);
void tablaProtocolo(char a, char b);
int hexa(char caracter,int a,int b);

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
    int c=0, i=0, j=3, k=1, v1=0, v2=0, v3=0;
    char caracter1=0, caracter2=0;

    while((caracter1 = fgetc(archivo)) != EOF){
        printf("%d ",c);
        if(caracter1 == '\n' && caracter2 == '\n'){
            printf("\nSubCapa MAC\nDireccion MAC destino:\t");
            for(i=0;i<12;i++)
              printf("%c",DirecMACDest[i]);
            printf("\nDireccion MAC Origen:\t");
            for(i=0;i<12;i++)
              printf("%c",DirecMACOrg[i]);
            printf("\nLongitud:\t");
            for(i=0;i<4;i++)
              printf("%c",EthertypeAux[i]);
            printf("\t=\t%d\n\tSubCapa LLC\nDSAP:\t0x", Ethertype);
            for(i=0;i<2;i++)
              printf("%c",DSAP[i]);

            if(DSAP[1]=='0')
                printf("\t11110000\tIndividual\t-\t");
            else
                printf("\t11110001\tGrupo\t-\t");
            
            tablaProtocolo(DSAP[0], DSAP[1]);
            printf("SSAP:\t0x");
            for(i=0;i<2;i++)
              printf("%c",SSAP[i]);

            if(SSAP[1]=='0')
                fputs("\t11110000\nComando\t", Nv_arch);
            else
                fputs("\t11110000\tRespuesta\t", Nv_arch);
            

            tablaProtocolo(SSAP[0],SSAP[1]);
            printf("Control:\t0x");
            for(i=0; i<4; i++)
              printf("%c",ControlAux[i]);
            printf("\t");

            for(i=0; i<7; i++)
                printf("%c",Control1[i]);

            printf(" %c\t", Control1[7]);
            v2=0;

            for(i=0; i<7; i++)
                printf("%c",Control2[i]);

            printf(" %c", Control2[7]);
            v3=0;

            for(i=6, j=0; 0<=i; i--, j++){
                if(Control1[i]==1)
                    v2 += potencia(2,j);
                if(Control1[i]==1)
                    v3 += potencia(2,j);
            }

            printf("\n\t\t\tN(S) = %c",v2);

            if(Control1[7] == 0)
                printf("\t Informacion\tN(R) = ");
            else
                printf("\t Otro\tN(R) = ");

            printf("%c",v3);

            if(Control2[7] == 0)
                printf("\t P/F = \t");
            else
                printf("\t P/F = \t");

            printf("%c\n\n\n", Control2[7]);

            c=0, i=0, j=3, k==1, v1=0, v2=0, v3=0;
        }else{
            if(caracter1 != ' ' && caracter1 != '\n'){
                if(c==17 || c==35 || c==41 || c==44 || c==47 || c==54)
                    i==0;
                else if(c<17){
                    DirecMACDest[i]=caracter1;
                    i++;
                }else if(17<c<35){
                    DirecMACOrg[i]=caracter1;
                    i++;
                }else if(35<c<41){               //Ethertype 00x0000
                    EthertypeAux[i]=caracter1;
                    v1 += hexa(caracter1, v1, j);
                    i++;
                    j--;
                }else if(41<c<44){                      //DSAP 0x00
                    DSAP[i]=caracter1;
                    i++;
                }else if(44<c<47){                        //SSAP 0x00
                    SSAP[i]=caracter1;
                    i++;
                }else if(49<c<55){
                    if(i==2)
                        k==1;
                    
                    if(i<2){
                        caracter2=ControlAux[i];
                        v2 += hexa(caracter2, v2, k);
                    }else{
                        caracter2=ControlAux[i];
                        v3 += hexa(caracter2, v2, k);
                    }
                    i++;
                }else if(c==55){
                    for(j=0; j<7; j++){
                        Control1[j]=0;
                        Control2[j]=0;
                    }
                    
                    while(v2 != 0 || v2 != 1){
                        ConA[i]=v2%2;
                        v2 = v2/2;
                        i++;
                    }

                    for(j=(8-i); j<8; j++)
                        Control1[j]==ConA[8-j];

                    i=0;
                    
                    while(v3 != 0 || v3 != 1){
                        ConA[i]=v3%2;
                        v3 = v3/2;
                        i++;
                    }

                    for(j=(8-i); j<8; j++)
                        Control2[j]==ConA[8-j];
                }
            }
        }
        caracter2=caracter1;
        c++;
        printf("_%c_ ",caracter1);
    }
}

void tablaProtocolo(char a, char b){
  if(a=='0')
    if(b=='0')
      printf("Null LSAP");
    else if(b=='2')
      printf("Individual LLC SUBlayer Management Function");
    else if(b=='3')
      printf("Group LLC Sublayer Management Function");
    else if(b=='4')
      printf("IBM SNA Path Control (individual)");
    else if(b=='5')
      printf("IBM SNA Path Control (group)");
    else if(b=='6')
      printf("ARPANET Internet Protocol (IP)");
    else if(b=='E')
      printf("PROWAY (IEC955) Network Management & Initialization");
    else if(b=='8' || b=='C')
      printf("SNA");
    
  if(a=='F')
    if(b=='0')
      printf("IBM NetBIOS");
    else if(b=='4')
      printf("IBM LAN Management (Individual)");
    else if(b=='5')
      printf("IBM LAN Management (Group)");
    else if(b=='8')
      printf("IBM Remote Program Load (RPL)");
    else if(b=='A')
      printf("Ungermann-Bass");
    else if(b=='E')
      printf("ISO Network Layer Protocol");
    else if(b=='F')
      printf("Global LSAP");
    
  if(a=='8')
    if(b=='0')
      printf("Xerox Netwoork Systems (XNS)");
    else if(b=='6')
      printf("Nestar");
    else if(b=='E')
      printf("PROWAY (IEC 955) Active Station List Maintenance");
    
    if(a=='4')
      if(b=='2')
        printf("IEEE 802.1 Bridge Spanning Tree Protocol");
      else if(b=='E')
        printf("EIA RS-511 Manofacturing Message Service");
    
  if(b=='8')
    if(a=='1')
      printf("Texas Instruments");
    else if(a=='9')
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

int hexa(char caracter1, int a, int b){
    if('0'<=caracter1<='9'){
        int c=caracter1 - '0';
        a+=c*potencia(16,b);
    }else{
        if(caracter1=='a')
            a+=10*potencia(16,b);
        else if(caracter1=='b')
            a+=11*potencia(16,b);
        else if(caracter1=='c')
            a+=12*potencia(16,b);
        else if(caracter1=='d')
            a+=13*potencia(16,b);
        else if(caracter1=='e')
            a+=14*potencia(16,b);
        else if(caracter1=='f')
            a+=15*potencia(16,b);
        else
            printf("\nError en Ethertype\n");
    }

    return a;
}

int potencia(int a, int b){
    int c=a;

    for(int i=0; i<(b-1); i++)
        c*=a;

    return c;
}