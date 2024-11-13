#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
    int completed;
};

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0, completedProcesses = 0;

    while (completedProcesses < n) {
        int shortest = -1;
        int minBurst = 1e9;

        // Find process with shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrivalTime <= currentTime && p[i].burstTime < minBurst) {
                minBurst = p[i].burstTime;
                shortest = i;
            }
        }

        // If no process is available, advance time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Process the selected process
        p[shortest].finishTime = currentTime + p[shortest].burstTime;
        p[shortest].turnaroundTime = p[shortest].finishTime - p[shortest].arrivalTime;
        p[shortest].waitingTime = p[shortest].turnaroundTime - p[shortest].burstTime;
        
        // Mark as completed and update currentTime
        p[shortest].completed = 1;
        completedProcesses++;
        currentTime = p[shortest].finishTime;
    }
}

void displayProcessInfo(struct Process p[], int n) {
    printf("ID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", 
               p[i].id, p[i].arrivalTime, p[i].burstTime, 
               p[i].finishTime, p[i].turnaroundTime, p[i].waitingTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].completed = 0;
    }

    // Calculate times using Non-Preemptive SJF scheduling
    calculateTimes(p, n);

    // Display process information with calculated times
    printf("\nProcess information:\n");
    displayProcessInfo(p, n);

    return 0;
}
