#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 5

pthread_mutex_t read_write_lock;
pthread_mutex_t count_lock;
int read_count = 0; // Number of active readers
int shared_data = 0; // Shared resource

// Reader thread function
void *reader(void *arg) {
    int reader_id = *((int *)arg);

    // Lock for reading
    pthread_mutex_lock(&count_lock);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&read_write_lock); // Lock the resource if it's the first reader
    }
    pthread_mutex_unlock(&count_lock);

    // Reading
    printf("Reader %d: reading data = %d\n", reader_id, shared_data);
    sleep(1); // Simulate reading time

    // Unlock for reading
    pthread_mutex_lock(&count_lock);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&read_write_lock); // Unlock the resource if it's the last reader
    }
    pthread_mutex_unlock(&count_lock);

    pthread_exit(0);
}

// Writer thread function
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    // Lock for writing
    pthread_mutex_lock(&read_write_lock);
    
    // Writing
    shared_data++;
    printf("Writer %d: writing data = %d\n", writer_id, shared_data);
    sleep(1); // Simulate writing time
    
    pthread_mutex_unlock(&read_write_lock);
    pthread_exit(0);
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    // Initialize mutexes
    pthread_mutex_init(&read_write_lock, NULL);
    pthread_mutex_init(&count_lock, NULL);

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all readers to finish
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writers to finish
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&read_write_lock);
    pthread_mutex_destroy(&count_lock);

    return 0;
}
