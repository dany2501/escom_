#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

FILE * archivo;

int auxiliar1[8], auxiliar2[8], t;

void NS_NR(int);
void supervision();
void PF(int);
void tipo();
void cero();
int hexa(char, int);
void tablaProtocolo(char, char);
int potencia(int, int);
void bin(int, int);

int main(int argc, char *argv[]){
    int i, j, v, w, x, y, z=1;
    char aux[8]={'0','0','0','0','0','0','0','0'}, cad[50], caracter1, caracter2=0;

    if(argc != 2){
        printf("\nSe requiere el nombre del archivo txt de tramas y el nombre del nuevo txt\n\n");
        exit(0);
    }

    archivo = fopen(argv[1],"r");

    if (archivo==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }

    while((caracter1 = fgetc(archivo)) != EOF){
        i=0;

        printf("\n\t\tTRAMA %d\n\n",z);
        
        do{
            cad[i]=caracter1;
            i++;
        }while((caracter1 = fgetc(archivo)) != '\n' || i < 48);

        cad[i]='\0';

        printf("\nSubCapa MAC\n\nDireccion MAC destino:\t");
            
        for(i=0; i<17; i++)
            printf("%c",cad[i]);
            
        printf("\nDireccion MAC Origen:\t");

        for(i=18; i<35; i++)
            printf("%c",cad[i]);

        printf("\nLongitud: ");

        for(i=36, j=3, v=0; i<41; i++, j--){
            printf("%c",cad[i]);

            if(cad[i]==' ')
                j++;
            else
                v += hexa(cad[i], j);
        }

        printf(" = %d\n\nSubCapa LLC\n\nDSAP: 0x",v);

        for(v=0,w=0,i=42,j=1;i<47;i++,j--)
            if(i != 44){
                if(i<44){
                    v+=hexa(cad[i],j);
                    printf("%c",cad[i]);
                }else if(44<i)
                    w+=hexa(cad[i],j);
            }else{
                j=2;
                printf("  ");
        }

        cero();
        bin(v,0);
        bin(w,0);

        for(i=7;i<=0;i--)
            printf("%d",auxiliar1[i]);

        if(auxiliar1[0]=='0')
            printf("  Individual - ");
        else
            printf("  Grupo - ");
            
        tablaProtocolo(cad[42],cad[43]);
        printf("\nSSAP: 0x%c%c  ",cad[45],cad[46]);

        for(i=7;i<=0;i--)
            printf("%d",auxiliar2[i]);

        if(auxiliar2[0]=='0')
            printf("  Comando - ");
        else
            printf("  Respuesta - ");
            
        tablaProtocolo(cad[45],cad[46]);
        i=0;

        setbuf(stdin, NULL);
        setbuf(stdout, NULL);

        __fpurge(stdin);
        __fpurge(stdout);

        while((caracter1 = fgetc(archivo))!= '\n'){
            cad[i]=caracter1;
            i++;
        }

        cad[i]='\0';

        printf("\nControl:  0x");

        for(i=0,j=1,v=0,w=0,x=3,y=0; i<5; i++, j--,x--)
            if(i!=2){
                printf("%c",cad[i]);
                y+=hexa(cad[i],x);

                if(i<2)
                    v += hexa(cad[i], j);
                else if(2<i)
                    w += hexa(cad[i], j);
            }else{
                printf("_");
                j=2;
            }

        printf("\t");
        cero();
        bin(v,0);
        bin(w,1);

        if(auxiliar1[0]=='1' && auxiliar1[1]=='1'){
            printf("\n\nTipo 3: Trama no Enumerada\n\n");
            tipo();
            NS_NR(0);
            printf("\tN(S) = %d\t P/F = ",v);
            PF(0);
        }else if(auxiliar1[0]=='1' && auxiliar1[1]=='0'){
            printf("\n\nTipo 2: Trama de Supervision\n\n");
            NS_NR(0);
            printf("\t\t");
            NS_NR(1);
            printf("\nSupervision: ");
            supervision();
            printf("\t\tN(R) = %i\tP/F = ",w);
            PF(1);
        }else{
            printf("\n\nTipo 1: Trama de Informacion\n\n");
            NS_NR(0);
            NS_NR(1);
            printf("\nN(S) = %i\tN(R) = %i\tP/F = ",v,w);
            PF(1);
        }

        printf("SOBRA:\n");

        {
            i=0;
            do{
                cad[i]=caracter1;
                printf(".%c",cad[i]);
                i++;
            }while((caracter1 = fgetc(archivo))!= EOF && caracter1 != '\n');
        }while((caracter1 = fgetc(archivo)) != EOF && cad[0]!='\n');
        
        z++;
    }

    fclose(archivo);

    return 0;
}

void NS_NR(int a){
    if(a==0){
        for(int i=7;0<i;i--)
            printf("%d",auxiliar1[i]);

        printf(" %d\t",auxiliar1[0]);
    }else{
        for(int i=7;0<i;i--)
            printf("%d",auxiliar2[i]);

        printf(" %d\t",auxiliar2[0]);
    }
}

void supervision(){
    if(auxiliar1[2]=='0')
        if(auxiliar1[3]=='0')
            printf("Receive Ready (RR)");
        else
            printf("Receive Not Ready (RNR)");
    else
        if(auxiliar1[3]=='0')
            printf("Reject (REJ)");
        else
            printf("Selective Reject (SREJ)");
}

void PF(int a){
    if(a=0){
        if(auxiliar1[4]=='1')
            printf("P\n\n");
        else
            printf("F\n\n");
    }else{
        if(auxiliar2[0]=='1')
            printf("P\n\n");
        else
            printf("F\n\n");
    }
}

void tipo(){
    if(strcmp(auxiliar1,"11000001")==0)
        printf("Set normal response SNRM");
    else if(strcmp(auxiliar1,"11110011")==0)
        printf("Set normal response extended mode SNRME");
    else if(strcmp(auxiliar1,"11110000")==0)
        printf("Set asynchronous response SARM");
    else if(strcmp(auxiliar1,"11110010")==0)
        printf("Set asynchronous response extended mode SARME");
    else if(strcmp(auxiliar1,"11110100")==0)
        printf("Set asynchronous balanced mode SABM");
    else if(strcmp(auxiliar1,"11110110")==0)
        printf("Set asynchronous balanced extended mode SABME");
    else if(strcmp(auxiliar1,"11100000")==0)
        printf("Set initialization dmode SIM");
    else if(strcmp(auxiliar1,"11000010")==0)
        printf("Disconnect DISC");
    else if(strcmp(auxiliar1,"11001110")==0)
        printf("Unnumbered Acknowledgment UA");
    else if(strcmp(auxiliar1,"11111000")==0)
        printf("Disconnect Mode DM");
    else if(strcmp(auxiliar1,"11001010")==0)
        printf("Request Disconnect RD");
    else if(strcmp(auxiliar1,"11101000")==0)
        printf("Request Initialization Mode RIM");
    else if(strcmp(auxiliar1,"11001000")==0 || strcmp(auxiliar1,"11000000")==0)
        printf("Unnumbered Information UI");
    else if(strcmp(auxiliar1,"11000100")==0)
        printf("Unnumbered Poll UP");
    else if(strcmp(auxiliar1,"11110001")==0)
        printf("Reset RSET");
    else if(strcmp(auxiliar1,"11110101")==0 || strcmp(auxiliar1,"11111101")==0)
        printf("Exchange Identification XID");
    else if(strcmp(auxiliar1,"11000111")==0 || strcmp(auxiliar1,"11001111")==0)
        printf("Test TEST");
    else
        printf("Otro");
}

void cero(){
    int i=0;

    for(i=0;i<8;i++){
        auxiliar1[i]=0;
        auxiliar2[i]=0;
    }
}

int potencia(int a, int b){
    int c, i;

    if(b==0)
        return 1;
    else if (b==1)
        return a;
    else{
        c=a;

        for(i=1; i<b; i++){
            c*=a;
        }
    }
    return c;
}

void bin(int a, int b){
    int i=0;

    while(a != 0){
        if(b==0)
            auxiliar1[i]=a%2;
        else
            auxiliar2[i]=a%2;
        a = a/2;
        i++;
    }
}

int hexa(char caracter1, int a){
    int i=potencia(16,a);

    if(caracter1=='a' || caracter1=='A')
        return 10*i;
    else if(caracter1=='b' || caracter1=='B')
        return 11*i;
    else if(caracter1=='c' || caracter1=='C')
        return 12*i;
    else if(caracter1=='d' || caracter1=='D')
        return 13*i;
    else if(caracter1=='e' || caracter1=='E')
        return 14*i;
    else if(caracter1=='f' || caracter1=='F')
        return 15*i;
    else if('0'<=caracter1<='9'){
        int c=caracter1 - '0';
        return c*i;
    }else{
            printf("\nError en Ethertype\n");
            exit(0);
    }
}

void tablaProtocolo(char a, char b){
    if(a=='0'){
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
        else if(b=='E' || b=='e')
            printf("PROWAY (IEC955) Network Management & Initialization");
        else if(b=='8' || b=='C' || b=='c')
            printf("SNA");
        else
            printf("Error");
    }
    
    else if(a=='F' || a== 'f'){
        if (b=='0')
            printf("IBM NetBIOS");
        else if(b=='4')
            printf("IBM LAN Management (Individual)");
        else if(b=='5')
            printf("IBM LAN Management (Group)");
        else if(b=='8')
            printf("IBM Remote Program Load (RPL)");
        else if(b=='A' || b=='a')
            printf("Ungermann-Bass");
        else if(b=='E' || b=='e')
            printf("ISO Network Layer Protocol");
        else if(b=='F' || b=='f')
            printf("Global LSAP");
        else
            printf("Error");
    }
    
    else if(a=='8'){
        if(b=='0')
            printf("Xerox Netwoork Systems (XNS)");
        else if(a=='8' && b=='6')
            printf("Nestar");
        else if(a=='8' && (b=='E' || b== 'e'))
            printf("PROWAY (IEC 955) Active Station List Maintenance");
        else
            printf("Error");
    }
        
    
    else if(a=='4'){
        if(b=='2')
            printf("IEEE 802.1 Bridge Spanning Tree Protocol");
        else if(b=='E' || b== 'e')
            printf("EIA RS-511 Manofacturing Message Service");
        else
            printf("Error");
    }
    
    else if(b=='8'){
        if(a=='1')
            printf("Texas Instruments");
        else if(a=='9')
            printf("ARPANET Address Resolution Protocol (ARP)");
        else
            printf("Error");
    }
    
    else if(a=='7' && (b=='E' || b== 'e'))
        printf("ISO 8280 (X.25 over IEEE 802.2 Type 2 LLC)");
    else if((a=='B' || a=='b') && (b=='C' || b== 'c'))
        printf("Banyan VINES");
    else if((a=='A' || a=='a') &&  (b=='A' || b== 'a'))
        printf("SubNetwork Access Protocol (SNAP)");
    else if((a=='E' || a== 'e') && b=='0')
        printf("Novell NetWare");

    else
        printf("No se encontro");
}