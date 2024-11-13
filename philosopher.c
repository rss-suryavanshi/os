#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5  // Number of philosophers

// Define semaphores and other global variables
sem_t forks[NUM_PHILOSOPHERS]; // One semaphore per fork

void *philosopher(void *arg) {
    int philosopherId = *(int *)arg;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", philosopherId);
        sleep(1); // Simulate thinking time

        // Pick up left fork
        sem_wait(&forks[philosopherId]);
        printf("Philosopher %d picked up left fork %d\n", philosopherId, philosopherId);

        // Pick up right fork
        sem_wait(&forks[(philosopherId + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork %d\n", philosopherId, (philosopherId + 1) % NUM_PHILOSOPHERS);

        // Eating
        printf("Philosopher %d is eating...\n", philosopherId);
        sleep(1); // Simulate eating time

        // Put down right fork
        sem_post(&forks[(philosopherId + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork %d\n", philosopherId, (philosopherId + 1) % NUM_PHILOSOPHERS);

        // Put down left fork
        sem_post(&forks[philosopherId]);
        printf("Philosopher %d put down left fork %d\n", philosopherId, philosopherId);

        // Back to thinking (loop continues)
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIds[NUM_PHILOSOPHERS];

    // Initialize semaphores for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1); // Each fork is initially available
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopherIds[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopherIds[i]);
    }

    // Wait for all philosophers to complete (though they will loop indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (not reached in this code since it loops infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
