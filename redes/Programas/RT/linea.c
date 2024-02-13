#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE * archivo;
FILE * Nv_arch;

int auxiliar1[8]={'0', '0', '0', '0', '0', '0', '0', '0'}, auxiliar2[8]={'0', '0', '0', '0', '0', '0', '0', '0'};

int hexa(char caracter1, int b);
void tablaProtocolo(char a, char b);
int potencia(int a, int b);
void bin(int a, int b);

int main(int argc, char *argv[]){
    int c=0, i=0, j=0, v=0, w=0;
    char aux[8]={'0','0','0','0','0','0','0','0'}, cad[50], caracter1=0, caracter2=0;

    if(argc != 3){
        printf("\n\nSe requiere el nombre del archivo txt de tramas y el nombre del nuevo txt\n\n");
        exit(0);
    }

    if ((archivo = fopen(argv[1],"r"))==NULL || (Nv_arch = fopen(argv[2],"w"))==NULL){
        perror ("\nError al abrir archivo");
        exit(-1);
    }

    printf("\n\t\tTRAMAS\n\n");

    while(fgets(cad,50,archivo) != NULL){
        i=0;
        v=0;

        while(cad != NULL && cad != "\n")
            fgets(cad,50,archivo);

        if(cad=="\n")
            fgets(cad,50,archivo);

        printf("%s\n\n", cad);
        printf("SubCapa MAC\nDireccion MAC destino:\t");
                
        for(i=0; i<17; i++)
            printf("%c",cad[i]);
                
        printf("\nDireccion MAC Origen:\t");

        for(i=18; i<35; i++)
            printf("%c",cad[i]);

        printf("\nLongitud: ");

        for(i=36, j=3; i<41; i++, j--){
            printf("%c",cad[i]);

            if(cad[i]==' ')
                j++;
            else
                v += hexa(cad[i], j);
        }

        printf(" = %d\n\n\tSubCapa LLC\n\nDSAP: 0x%c%c",v,cad[42],cad[43]);

        if(cad[43]=='0')
            printf("  11110000  Individual - ");
        else
            printf("  11110001  Grupo - ");
                
        tablaProtocolo(cad[42],cad[43]);
        printf("\nSSAP: 0x%c%c",cad[45],cad[46]);

        if(cad[46]=='0')
            printf("  11110000  Comando - ");
        else
            printf("  11110001  Respuesta - ");
                
        tablaProtocolo(cad[45],cad[46]);
        printf("\nControl:  0x");

        fgets(cad,50,archivo);

        for(v=0, w=0, i=0, j=1; i<5; i++, j--){
            fflush(stdout);
            printf("%c",cad[i]);

            if(i<51)
                v += hexa(cad[i], j);
            if(51<i)
                w += hexa(cad[i], j);
            if(i==51)
                j=2;
        }

        printf("\t");
        bin(v,0);

        for(j=7;0<j;j++)
            printf("%d",auxiliar1[j]);

        printf(" %d\t",auxiliar1[0]);
                
        bin(w,1);

        for(j=7;0<j;j++)
            printf("%d",auxiliar2[j]);

        printf(" %d\t",auxiliar2[0]);

        for(v=0, w=0, i=1, j=0; i<8; i++, j++){
            if(auxiliar1[i]==1)
                v += potencia(2,j);
            if(auxiliar2[i]==1)
                w += potencia(2,j);
        }

        printf("\n\t\t\tN(S) = %i",v);

            if(auxiliar1[0] == 0)
                printf("\t Informacion\tN(R) = %i",w);
            else
                printf("\t Otro\tN(R) = %i",w);
            
            printf("\t P/F =  %c\n\n\n",auxiliar2[0]);
        }
    }

    fclose(archivo);
    fclose(Nv_arch);

    return 0;
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
    if(a=='0' && b=='0')
        printf("Null LSAP");
    else if(a=='0' && b=='2')
        printf("Individual LLC SUBlayer Management Function");
    else if(a=='0' && b=='3')
        printf("Group LLC Sublayer Management Function");
    else if(a=='0' && b=='4')
        printf("IBM SNA Path Control (individual)");
    else if(a=='0' && b=='5')
        printf("IBM SNA Path Control (group)");
    else if(a=='0' && b=='6')
        printf("ARPANET Internet Protocol (IP)");
    else if(a=='0' && (b=='E' || b=='e'))
        printf("PROWAY (IEC955) Network Management & Initialization");
    else if(a=='0' && (b=='8' || b=='C' || b=='c'))
        printf("SNA");
    
    else if((a=='F' || a== 'f') && b=='0')
        printf("IBM NetBIOS");
    else if((a=='F' || a== 'f') && b=='4')
        printf("IBM LAN Management (Individual)");
    else if((a=='F' || a== 'f') && b=='5')
        printf("IBM LAN Management (Group)");
    else if((a=='F' || a== 'f') && b=='8')
        printf("IBM Remote Program Load (RPL)");
    else if((a=='F' || a== 'f')  && (b=='A' || b=='a'))
        printf("Ungermann-Bass");
    else if((a=='F' || a== 'f') && (b=='E' || b=='e'))
        printf("ISO Network Layer Protocol");
    else if((a=='F' || a== 'f') && (b=='F' || b=='f'))
        printf("Global LSAP");
    
    else if(a=='8' && b=='0')
        printf("Xerox Netwoork Systems (XNS)");
    else if(a=='8' && b=='6')
        printf("Nestar");
    else if(a=='8' && (b=='E' || b== 'e'))
        printf("PROWAY (IEC 955) Active Station List Maintenance");
    
    else if(a=='4' && b=='2')
        printf("IEEE 802.1 Bridge Spanning Tree Protocol");
    else if(a=='4' && (b=='E' || b== 'e'))
        printf("EIA RS-511 Manofacturing Message Service");
    
    else if(a=='1' && b=='8')
        printf("Texas Instruments");
    else if(a=='9' && b=='8')
        printf("ARPANET Address Resolution Protocol (ARP)");
    
    else if(a=='7' && (b=='E' || b== 'e'))
        printf("ISO 8280 (X.25 over IEEE 802.2 Type 2 LLC)");
    else if(a=='B' && (b=='C' || b== 'c'))
        printf("Banyan VINES");
    else if(a=='A' &&  (b=='A' || b== 'a'))
        printf("SubNetwork Access Protocol (SNAP)");
    else if((a=='E' || a== 'e') && b=='0')
        printf("Novell NetWare");

    else
        printf("No se encontro");
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

    while(a != 0 && a != 1){
        if(b==0)
            auxiliar1[i]=a%2;
        else
            auxiliar2[i]=a%2;
        a = a/2;
        i++;
    }
}