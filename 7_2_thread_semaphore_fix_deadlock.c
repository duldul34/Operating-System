#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

sem_t   mutex1,  mutex2;
int     buffer[4] = {10, 10, 10, 10};

void *producer(void *arg);
void *consumer(void *arg);

int main(void)
{
    pthread_t   id_p1, id_p2;

    sem_init(&mutex1, 0, 1); // initialize semaphore, mutex1 = 1;
    sem_init(&mutex2, 0, 1); // initialize semaphore, mutex2 = 1;

    pthread_create(&id_p1, NULL, producer, NULL);
    pthread_create(&id_p2, NULL, consumer, NULL);

    pthread_join(id_p1, NULL);
    pthread_join(id_p2, NULL);
}


void *consumer(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&mutex1);
        sleep(1);
        sem_wait(&mutex2);
        printf("Consumer read: %2d from %2d-th buffer\n", buffer[i % 4], i % 4);
        buffer[i % 4] = -1;
        sem_post(&mutex1);
        sem_post(&mutex2);
        sleep(1);
    }
}

void *producer(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&mutex1);
        sem_wait(&mutex2);
        printf("Producer write: %2d into %2d-th buffer", i, i % 4);
        buffer[i % 4] = i;
        sem_post(&mutex1);
        sem_post(&mutex2);
        sleep(1);
    }
}