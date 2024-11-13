#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void deadlock_detection(int n, int m, int available[], int allocation[][MAX_RESOURCES], int request[][MAX_RESOURCES]) {
    bool finished[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    bool deadlock = false;

    // Initialize work with the available resources
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (1) {
        bool found_process = false;

        // Check if there is a process that can finish
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {  // Process not yet completed
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        break;
                    }
                }

                // If all resources needed by process i can be allocated
                if (j == m) {
                    // Process i can finish; release its resources
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finished[i] = true;
                    found_process = true;
                }
            }
        }

        // If no process could be found to finish, break the loop
        if (!found_process) {
            break;
        }
    }

    // Check for deadlock
    printf("Deadlocked Processes: ");
    for (int i = 0; i < n; i++) {
        if (!finished[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (deadlock) {
        printf("\nSystem is in a deadlock state.\n");
    } else {
        printf("None\nSystem is not in a deadlock state.\n");
    }
}

int main() {
    int n, m;
    int available[MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    deadlock_detection(n, m, available, allocation, request);

    return 0;
}
