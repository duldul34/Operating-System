#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

sem_t   mutex, full, empty;
int     buffer[4] = {10, 10, 10, 10};

void *producer(void *arg);
void *consumer(void *arg);

int main(void)
{
    pthread_t   id_p1, id_p2;

    sem_init(&empty, 0, 4); // initialize semaphore, empty = 4;
    sem_init(&full, 0, 0); // initialize semaphore, full = 0;
    sem_init(&mutex, 0, 1); // initialize semaphore, mutex = 1;

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
        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumer read: %2d from %2d-th buffer\n", buffer[i % 4], i % 4);
        buffer[i % 4] = -1;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

void *producer(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("Producer write: %2d into %2d-th buffer", i, i % 4);
        buffer[i % 4] = i;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}