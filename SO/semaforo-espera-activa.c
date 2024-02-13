#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
int valA, valB;
sem_t secA1, secA2, secB1, secB2;
void* hiloProduce(void *idProduce)
{
    int productor = *(int *)idProduce, f;
    int secHiloPro = 0;
    for(f=0; f<20; f++)
    {
        while(sem_wait(&secA2) != 0)
            secHiloPro = 1;
        valA = f;
        printf("PRODUCTOR %d, PRODUCE %d \n", productor, valA);
        sem_post(&secA1);
        while(sem_wait(&secB2) != 0)
            secHiloPro = 0;
        valB = f+100;
        printf("PRODUCTOR %d, PRODUCE %d \n", productor, valB);
        sem_post(&secB1);
    }
    pthread_exit(NULL);
}
void* hiloConsume(void *idConsume)
{
    int consumidor = *(int *)idConsume, k;
    int secHiloCo = 0;
    for(k=0; k<20; k++)
    {
        while(sem_wait(&secA1) != 0)
            secHiloCo = 1;
        printf("CONSUMIDOR %d, CONSUME %d \n \n", consumidor, valA);
        sem_post(&secA2);
        while(sem_wait(&secB1) != 0)
            secHiloCo = 0;
        printf("CONSUMIDOR %d, CONSUME %d \n \n", consumidor, valB);
        sem_post(&secB2);
    }
    pthread_exit(NULL);
}
int main()
{
    int i, ids[2];
    pthread_t productor, consumidor;
    sem_init(&secA1, 5, 0);
    sem_init(&secA2, 5, 1);
    sem_init(&secB1, 5, 0);
    sem_init(&secB2, 5, 1);
    for(i=0; i<2; i++)
    {
        ids[i]=i;
        pthread_create(&productor, NULL, hiloProduce, &ids[i]);
        pthread_create(&consumidor, NULL, hiloConsume, &ids[i]);
    }
    for(i=0; i<2; i++)
    {
        pthread_join(productor, NULL);
        pthread_join(consumidor, NULL);
    }
    sem_destroy(&secA1);
    sem_destroy(&secA2);
    sem_destroy(&secB1);
    sem_destroy(&secB2);
    return 0;
}