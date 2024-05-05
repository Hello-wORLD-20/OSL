
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer;
int in = 0, out = 0;
int item = 0;
int buffer_size, max_items;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 0; i < max_items; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        item++;
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < max_items; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    printf("Enter the size of the buffer: ");
    scanf("%d", &buffer_size);
    buffer = (int *)malloc(buffer_size * sizeof(int));

    printf("Enter the number of items to produce/consume: ");
    scanf("%d", &max_items);

    pthread_t producerThread, consumerThread;
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    free(buffer);
    return 0;
}

