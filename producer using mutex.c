#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer
#define NUM_PRODUCERS 2 // Number of producer threads
#define NUM_CONSUMERS 2 // Number of consumer threads
#define NUM_ITEMS 10 // Total items to produce/consume

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Index for the next item to be produced
int out = 0; // Index for the next item to be consumed
pthread_mutex_t mutex; // Mutex for synchronizing access to buffer
pthread_cond_t full; // Condition variable for when the buffer is full
pthread_cond_t empty; // Condition variable for when the buffer is empty

// Producer thread function
void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce an item
        int item = rand() % 100; // Random item
        
        // Lock the mutex
        pthread_mutex_lock(&mutex);

        // Wait while the buffer is full
        while ((in + 1) % BUFFER_SIZE == out) {
            pthread_cond_wait(&full, &mutex);
        }

        // Add item to the buffer
        buffer[in] = item;
        printf("Producer %ld produced: %d\n", (long)arg, item);
        in = (in + 1) % BUFFER_SIZE; // Move the index to the next position

        // Signal that the buffer is not empty
        pthread_cond_signal(&empty);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate production time
        sleep(rand() % 2);
    }
    pthread_exit(0);
}

// Consumer thread function
void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Lock the mutex
        pthread_mutex_lock(&mutex);

        // Wait while the buffer is empty
        while (in == out) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Remove item from the buffer
        int item = buffer[out];
        printf("Consumer %ld consumed: %d\n", (long)arg, item);
        out = (out + 1) % BUFFER_SIZE; // Move the index to the next position

        // Signal that the buffer is not full
        pthread_cond_signal(&full);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate consumption time
        sleep(rand() % 2);
    }
    pthread_exit(0);
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    // Create producer threads
    for (long i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)i);
    }

    // Create consumer threads
    for (long i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)i);
    }

    // Wait for all producer threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Wait for all consumer threads to finish
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
