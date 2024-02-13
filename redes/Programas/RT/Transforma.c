/*#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char DirecMACDest[12], DirecMACOrg[12], EthertypeAux[4], DSAP[2], SSAP[2], ControlAux[4], Control1[8], Control2[8], ConA[8];
int Ethertype;

FILE * archivo;
FILE * Nv_arch;

void leeEscT();

int main(int argc, char *argv[]){
    char cadena[182];

    if(argc != 3){
        printf("\n\nSe requiere el nombre del archivo txt de tramas y el nombre del nuevo txt\n\n");
        exit(0);
    }

    archivo = fopen(argv[1],"r");
    Nv_arch = fopen(argv[2],"r+");

    if (archivo==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }
    
    if (Nv_arch==NULL){
        perror ("\nError al abrir Nv_archivo");
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

    fputs("\n\t\tTRAMAS\n\n", Nv_arch);

    while(fscanf(archivo,"%c",&caracter1) != EOF){
        if(caracter1=='\n' || caracter1==' ' || caracter1=='\t' || caracter1=='\0'){
        printf("BLANCO");
        c=0;
        }else{
            fprintf(Nv_arch,"%c",caracter1);
            printf("%c",caracter1);
        }
        caracter2=caracter1;
        c++;
    }
}











*/
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
    char cadena[182];

    printf("0");
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
    printf("1");
    leeEscT();

    fclose(archivo);
    fclose(Nv_arch);
    return 0;
}

void leeEscT(){
    int c=0, i=0, j=3, k=1, v1=0, v2=0, v3=0, z=0;
    char caracter1=0, caracter2=0;

    printf("2");

    if(fputs("\n\t\tTRAMAS\n\n", Nv_arch)==EOF || fputs("\n\t\tTRAMAS\n\n", Nv_arch)<0){
        printf("Error en la escritura\n\n");
        exit(-1);
    }

    printf("3");

    while((caracter1 = fgetc(archivo)) != EOF){

    printf("4");
        printf("%d ",c);
        if(caracter1 == '\n' && caracter2 == '\n'){
//        if(c==55){
            printf("\nEntro a tramas1.txt\n");
//            fprintf(Nv_arch,"SubCapa MAC\nDireccion MAC destino:\t");
            if(fputs("SubCapa MAC",Nv_arch)==EOF){
                printf("Error en la escritura\n\n");
                exit(-1);
            }
            printf("Yaaaaaa\n\n");
            fputs("Direccion MAC destino:\t", Nv_arch);
            fputs(DirecMACDest, Nv_arch);
            fputs("\nDireccion MAC Origen:\t", Nv_arch);
            fputs(DirecMACOrg, Nv_arch);
            fputs("\nLongitud:\t", Nv_arch);
            fputs(EthertypeAux, Nv_arch);
            fputs("\t=\t", Nv_arch);
            fputc(Ethertype, Nv_arch);
            fputs("\n\tSubCapa LLC\nDSAP:\t0x", Nv_arch);
            fputs(DSAP, Nv_arch);

            if(DSAP[1]=='0')
                fputs("\t11110000\tIndividual\t-\t", Nv_arch);
            else
                fputs("\t11110001\tGrupo\t-\t", Nv_arch);
            
            tablaProtocolo(DSAP[0], DSAP[1]);
            fputs("SSAP:\t0x", Nv_arch);
            fputs(SSAP, Nv_arch);

            if(SSAP[1]=='0')
                fputs("\t11110000\nComando\t", Nv_arch);
            else
                fputs("\t11110000\tRespuesta\t", Nv_arch);
            

            tablaProtocolo(SSAP[0],SSAP[1]);
            fputs("Control:\t0x", Nv_arch);
            fputs(ControlAux, Nv_arch);
            fputs("\t", Nv_arch);

            for(i=0; i<7; i++)
                fputc(Control1[i], Nv_arch);

            fputs(" ", Nv_arch);
            fputc(Control1[7], Nv_arch);
            v2=0;

            for(i=0; i<7; i++)
                fputc(Control2[i], Nv_arch);

            fputs(" ", Nv_arch);
            fputc(Control2[7], Nv_arch);
            v3=0;

            for(i=6, j=0; 0<=i; i--, j++){
                if(Control1[i]==1)
                    v2 += potencia(2,j);
                if(Control1[i]==1)
                    v3 += potencia(2,j);
            }

            fputs("\n\t\t\tN(S) = ", Nv_arch);
            fputc(v2, Nv_arch);

            if(Control1[7] == 0)
                fputs("\t Informacion\tN(R) = ", Nv_arch);
            else
                fputs("\t Otro\tN(R) = ", Nv_arch);

            fputc(v3, Nv_arch);

            if(Control2[7] == 0)
                fputs("\t P/F = \t", Nv_arch);
            else
                fputs("\t P/F = \t", Nv_arch);

            fputc(Control2[7], Nv_arch);
            fputs("\n\n\n", Nv_arch);

            c=0, i=0, j=3, k==1, v1=0, v2=0, v3=0;
            z++;
            printf("Z = %d\n",z);
        }else{
            if('0'<=caracter1<='9' || 'a'<=caracter1<='z'){
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
    }
}

void tablaProtocolo(char a, char b){
    if(a=='0')
        if(b=='0')
            fputs("Null LSAP", Nv_arch);
        else if(b=='2')
            fputs("Individual LLC SUBlayer Management Function", Nv_arch);
        else if(b=='3')
            fputs("Group LLC Sublayer Management Function", Nv_arch);
        else if(b=='4')
            fputs("IBM SNA Path Control (individual)", Nv_arch);
        else if(b=='5')
            fputs("IBM SNA Path Control (group)", Nv_arch);
        else if(b=='6')
            fputs("ARPANET Internet Protocol (IP)", Nv_arch);
        else if(b=='E')
            fputs("PROWAY (IEC955) Network Management & Initialization", Nv_arch);
        else if(b=='8' || b=='C')
            fputs("SNA", Nv_arch);
    
    if(a=='F')
        if(b=='0')
            fputs("IBM NetBIOS", Nv_arch);
        else if(b=='4')
            fputs("IBM LAN Management (Individual)", Nv_arch);
        else if(b=='5')
            fputs("IBM LAN Management (Group)", Nv_arch);
        else if(b=='8')
            fputs("IBM Remote Program Load (RPL)", Nv_arch);
        else if(b=='A')
            fputs("Ungermann-Bass", Nv_arch);
        else if(b=='E')
            fputs("ISO Network Layer Protocol", Nv_arch);
        else if(b=='F')
            fputs("Global LSAP", Nv_arch);
    
    if(a=='8')
        if(b=='0')
            fputs("Xerox Netwoork Systems (XNS)", Nv_arch);
        else if(b=='6')
            fputs("Nestar", Nv_arch);
        else if(b=='E')
            fputs("PROWAY (IEC 955) Active Station List Maintenance", Nv_arch);
    
    if(a=='4')
        if(b=='2')
            fputs("IEEE 802.1 Bridge Spanning Tree Protocol", Nv_arch);
        else if(b=='E')
            fputs("EIA RS-511 Manofacturing Message Service", Nv_arch);
    
    if(b=='8')
        if(a=='1')
                fputs("Texas Instruments", Nv_arch);
        else if(a=='9')
                fputs("ARPANET Address Resolution Protocol (ARP)", Nv_arch);
    
    if(a=='7' && b=='E')
            fputs("ISO 8280 (X.25 over IEEE 802.2 Type 2 LLC)", Nv_arch);
    if(a=='B' && b=='C')
            fputs("Banyan VINES", Nv_arch);
    if(a=='A' && b=='A')
            fputs("SubNetwork Access Protocol (SNAP)", Nv_arch);
    if(a=='E' && b=='0')
        fputs("Novell NetWare", Nv_arch);
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