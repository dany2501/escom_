#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex,mutex2,mutex3,mutex4;
char a,b;
void constructor(void *args){
    int r = *(int *)args;
    int i;
    for (i = 0; i< 20;i ++){
        
        pthread_mutex_lock(&mutex);
        a = 'a';
        printf("P%d => %c\n",r,a);
        pthread_mutex_unlock(&mutex2);
        
        pthread_mutex_lock(&mutex3);
        b = 'b';
        printf("P%d => %c\n",r,b);
        pthread_mutex_unlock(&mutex4);
    }
    
}
void consumidor(void *args){
    int i;
    int r = *(int *)args;
    for (i = 0; i < 20; i++){

        pthread_mutex_lock(&mutex2);
        printf("C%d => %c\n",r,a);
        pthread_mutex_unlock(&mutex);
        
        pthread_mutex_lock(&mutex4);
        printf("C%d => %c\n",r,b);
        pthread_mutex_unlock(&mutex3);
    }
    
    
}

int main(int argc, char *argv[]){
    
    pthread_t producer, consumer;

    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_mutex_init(&mutex3,NULL);
    pthread_mutex_init(&mutex4,NULL);

    pthread_mutex_lock(&mutex2);
    pthread_mutex_lock(&mutex4);

    int arreglo[2];

    for (int i = 0;i<2;i++){
        arreglo[i]=i;
        pthread_create(&consumer, NULL,(void *)&consumidor, &arreglo[i]);
        pthread_create(&producer, NULL, (void *)&constructor, &arreglo[i]);
    }

    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);

    return 0;
}
