#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> /* superset of previous */
#include<unistd.h>
#include<arpa/inet.h>

void ser_enviar(char paq[1514]);//Funcion Como cliente
void ser_recibir();//Funcion como servidor

int menu();

int main(){
  char men[1514];
  printf("Chat");
  for(;;){
    switch (menu())
    {
    case 1:
      printf("\nEnviar: ");
      while(getchar()!='\n');
      fgets(men,1514,stdin);
      ser_enviar(men);
    break;
    
    case 2:
      ser_recibir();
    break;

    case 3:
      exit(0);
    break;
    default:
      printf("\nEsta opcion no existe");
    break;
    }
  }
  return 0;
}

int menu(){
  int opcion;
  printf("\n1.-Enviar mensaje");
  printf("\n2.-Recibir mensaje");
  printf("\n3.- salir");
  printf("\nOpcion:...");
  scanf("%d",&opcion);
  printf("\n");
  return opcion;
}

//Funcion que te permite ser un cliente
void ser_enviar(char paq[1514]){
  int udp_socket,lbind,tam;
  udp_socket=socket(AF_INET, SOCK_DGRAM,0);
  struct sockaddr_in local, remota;
  if(udp_socket==-1){
    perror("\nError al abrir el socket");
    exit(1);
  }
  else{
    perror("\nExito al abrir el socket");
    local.sin_family=AF_INET;
    local.sin_port=htons(0);
    local.sin_addr.s_addr=INADDR_ANY;//Internet address
    lbind=bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
    if(lbind==-1){
      perror("\nError en el bind");
      exit(0);
    }
    else
    {
      perror("\nExito en el bind");
      remota.sin_family=AF_INET;
      remota.sin_port=htons(8080);
      remota.sin_addr.s_addr=inet_addr("10.100.77.99");//Regresar 8.8.8.8 o poner la ip de la lap
      tam=sendto(udp_socket, paq, 1514, 0, (struct sockaddr *)&remota, sizeof(remota));
      if(tam==-1){
        perror("\nError al enviar");
        exit(1);
      }
      else
      {
        perror("\nExito al enviar");
      }
    }
    
  }
  close(udp_socket);
}

//Funcion que te convierte en servidor
void ser_recibir(){
  char paq[1514];
  int udp_socket,lbind,tam;
  int lrecv;
  udp_socket=socket(AF_INET, SOCK_DGRAM,0);
  struct sockaddr_in servidor, cliente;
  
  if(udp_socket==-1){
    perror("\nError al abrir el socket");
    exit(1);
  }

  else{
    perror("\nExito al abrir el socket");
    servidor.sin_family=AF_INET;
    servidor.sin_port=htons(8000);
    servidor.sin_addr.s_addr=INADDR_ANY;//Internet address
    lbind=bind(udp_socket, (struct sockaddr *)&servidor, sizeof(servidor));
  
    if(lbind==-1){
      perror("\nError en el bind");
      exit(0);
    }

    else{
      perror("\nExito en el bind");
      lrecv=sizeof(cliente);
      tam=recvfrom(udp_socket,paq,1514,0, (struct sockaddr *)&cliente,&lrecv);
      if(tam==-1){
        perror("\nError al recibir");
        exit(1);
      }
      else
      {
        printf("\nExito al recibir: %s\n", paq);
      }
    }
    
  }
  close(udp_socket);
}
