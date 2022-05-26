#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int     shared = 1;
sem_t   mutex, flag;

void *consumer(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&flag);
        sem_wait(&mutex);
        printf("Consumer decrease: %d\n", --shared);
        sem_post(&mutex);
        sleep(1);
    }
}

void *producer(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&mutex);
        printf("Producer increase: %d\n", ++shared);
        sem_post(&mutex);
        sem_post(&flag);
        sleep(2);
    }
}

int main(void)
{
    pthread_t   id_p1, id_p2;

    printf("Thread & Mutex\n");
    sem_init(&mutex, 0, 1); // initialize semaphore, mutex = 1;
    sem_init(&flag, 0, 0); // 동기화 도구로서의 세마포, flag = 0;

    pthread_create(&id_p1, NULL, producer, NULL);
    pthread_create(&id_p2, NULL, consumer, NULL);

    pthread_join(id_p1, NULL);
    pthread_join(id_p2, NULL);
}