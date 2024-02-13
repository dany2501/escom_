#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
char a,b;
sem_t s1, s2, s3, s4;
void constructor(void *args){
    int r = *(int *)args, f;
    for(f=0; f<20; f++)
    {
        sem_wait(&s2);
        a = 'a';
        printf("P%d => %c\n",r,a);
        sem_post(&s1);
        sem_wait(&s4);
        b = 'b';
        printf("P%d => %c\n",r,b);
        sem_post(&s3);
    }
    pthread_exit(NULL);
}
void consumidor(void *args){
    int r = *(int *)args, k;
    for(k=0; k<20; k++)
    {
        sem_wait(&s1);
        printf("C%d => %c\n",r,a);
        sem_post(&s2);
        sem_wait(&s3);
        printf("C%d => %c\n",r,b);
        sem_post(&s4);
    }
    pthread_exit(NULL);
}
int main()
{
    int arreglo[2];
    pthread_t producer, consumer;
    sem_init(&s1, 5, 0);
    sem_init(&s2, 5, 1);
    sem_init(&s3, 5, 0);
    sem_init(&s4, 5, 1);
    for (int i = 0;i<2;i++){
        arreglo[i]=i;
        pthread_create(&consumer, NULL,(void *)&consumidor, &arreglo[i]);
        pthread_create(&producer, NULL, (void *)&constructor, &arreglo[i]);
    }
    for(int i=0; i<2; i++)
    {
        pthread_join(producer, NULL);
        pthread_join(consumer, NULL);
    }
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    sem_destroy(&s4);
    return 0;
}