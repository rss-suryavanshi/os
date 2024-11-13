#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// Global variables
sem_t resourceAccess;   // Semaphore to access the shared resource
sem_t readCountAccess;  // Semaphore to protect readCount variable
int readCount = 0;      // Counter for the number of readers
int sharedData = 0;     // Shared resource

// Reader function
void *reader(void *arg) {
    int readerId = *(int *)arg;

    // Entry section for readers
    sem_wait(&readCountAccess);  // Lock to modify readCount
    readCount++;
    if (readCount == 1) {
        // First reader locks resource access
        sem_wait(&resourceAccess);
    }
    sem_post(&readCountAccess);  // Unlock readCountAccess

    // Critical section for reading
    printf("Reader %d: read sharedData = %d\n", readerId, sharedData);
    sleep(1); // Simulate reading time

    // Exit section for readers
    sem_wait(&readCountAccess);
    readCount--;
    if (readCount == 0) {
        // Last reader unlocks resource access
        sem_post(&resourceAccess);
    }
    sem_post(&readCountAccess);

    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writerId = *(int *)arg;

    // Entry section for writers
    sem_wait(&resourceAccess);  // Lock resource for exclusive access

    // Critical section for writing
    sharedData++;  // Modify the shared resource
    printf("Writer %d: wrote sharedData = %d\n", writerId, sharedData);
    sleep(1); // Simulate writing time

    // Exit section for writers
    sem_post(&resourceAccess);  // Unlock resource

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int readerIds[5], writerIds[5];

    // Initialize semaphores
    sem_init(&resourceAccess, 0, 1);
    sem_init(&readCountAccess, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < 5; i++) {
        readerIds[i] = i + 1;
        writerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&resourceAccess);
    sem_destroy(&readCountAccess);

    return 0;
}
