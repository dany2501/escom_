#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex,mutex2;
int seccion_critica;
void constructor(void *args){
    int i;
    for (i = 0; i< 20;i ++){
        
        pthread_mutex_lock(&mutex);
        seccion_critica = i;
        printf("P1 : %d\n",seccion_critica);
        pthread_mutex_unlock(&mutex2);

    }
    
}
void consumidor(void *args){
    int i;
    
    for (i = 0; i < 20; i++){

        pthread_mutex_lock(&mutex2);
        printf("C1 : %d\n",seccion_critica);
        pthread_mutex_unlock(&mutex);
    }
    
    
}

int main(int argc, char *argv[]){
    
    pthread_t producer, costumer;

    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex2,NULL);

    pthread_mutex_lock(&mutex2);

    pthread_create(&costumer, NULL,(void *)& consumidor, NULL);
    pthread_create(&producer, NULL, (void *)&constructor, NULL);

    pthread_join(producer,NULL);
    pthread_join(costumer,NULL);

    return 0;
}
