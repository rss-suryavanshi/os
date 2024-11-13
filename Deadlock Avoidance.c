#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m; // n = number of processes, m = number of resources

void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool is_safe(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, max, allocation);

    bool finish[MAX_PROCESSES] = {0}; // Track if each process can finish
    int safe_sequence[MAX_PROCESSES]; // Store the safe sequence
    int work[MAX_RESOURCES];

    // Initialize work with available resources
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0; // Number of processes that can complete

    while (count < n) {
        bool found = false;

        for (int p = 0; p < n; p++) {
            if (!finish[p]) { // Check if this process is not yet finished
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all resources for process p can be allocated
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[p][k];

                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process can be completed, return unsafe state
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    // If all processes can complete, return safe state
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safe_sequence[i]);
    printf("\n");

    return true;
}

int main() {
    int processes[MAX_PROCESSES], available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES], allocation[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    for (int i = 0; i < n; i++)
        processes[i] = i;

    printf("Enter the available resources for each type: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    is_safe(processes, available, max, allocation);

    return 0;
}
