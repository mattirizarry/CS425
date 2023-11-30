#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* buffer;
int in = 0;
int out = 0;

int produced = 0;
int consumed = 0;

int MAX_BUFFER_SIZE, UPPER_LIMIT;
int NUM_OF_PRODUCERS, NUM_OF_CONSUMERS;

pthread_spinlock_t spinlock;
pthread_cond_t full, empty;

void* producer(void* arg) {
    int item = 1;

    while (produced < UPPER_LIMIT) {
        pthread_spin_lock(&spinlock);

        while ((in + 1) % MAX_BUFFER_SIZE == out) {
            pthread_spin_unlock(&spinlock);
            continue;
        }

        buffer[in] = item++;

        in = (in + 1) % MAX_BUFFER_SIZE;

        produced++;

        pthread_cond_signal(&full);
        pthread_spin_unlock(&spinlock);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int id = *((int*)arg);

    while (consumed < UPPER_LIMIT) {
        pthread_spin_lock(&spinlock);

        while (in == out) {
            pthread_spin_unlock(&spinlock);
            continue;
        }

        int item = buffer[out];
        out = (out + 1) % MAX_BUFFER_SIZE;

        consumed++;

        pthread_cond_signal(&empty);
        pthread_spin_unlock(&spinlock);

        printf("%d, %d\n", id, item);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./spinlock_single_producer_single_consumer <buffer_size> <num_of_producers> <num_of_consumers> <upper_limit>\n");
        exit(EXIT_FAILURE);
    }

    MAX_BUFFER_SIZE = atoi(argv[1]);
    NUM_OF_PRODUCERS = atoi(argv[2]);
    NUM_OF_CONSUMERS = atoi(argv[3]);
    UPPER_LIMIT = atoi(argv[4]);

    buffer = malloc(sizeof(int) * MAX_BUFFER_SIZE);

    if (buffer == NULL) {
        printf("Error allocating memory for buffer\n");
        exit(EXIT_FAILURE);
    }

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_t producer_threads[NUM_OF_PRODUCERS], consumer_threads[NUM_OF_CONSUMERS];

    for (int i = 0; i < NUM_OF_PRODUCERS; i++) {
        int* thread_num = malloc(sizeof(int));

        *thread_num = i;

        pthread_create(&producer_threads[i], NULL, producer, thread_num);
    }

    for (int i = 0; i < NUM_OF_CONSUMERS; i++) {
        int* thread_num = malloc(sizeof(int));

        *thread_num = i;

        pthread_create(&consumer_threads[i], NULL, consumer, thread_num);
    }

    for (int i = 0; i < NUM_OF_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_OF_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_spin_destroy(&spinlock);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    free(buffer);

    return 0;
}
