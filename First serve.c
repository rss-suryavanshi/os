#include <stdio.h>

struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time (execution time) required by the process
    int finishTime;     // Finish time
    int turnaroundTime; // Turnaround time
    int waitingTime;    // Waiting time
};

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, fast-forward time to its arrival
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }
        
        // Calculate finish time for the process
        p[i].finishTime = currentTime + p[i].burstTime;
        
        // Calculate turnaround time and waiting time
        p[i].turnaroundTime = p[i].finishTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        
        // Update current time to the finish time of the current process
        currentTime = p[i].finishTime;
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

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    // Calculate times using FCFS scheduling
    calculateTimes(p, n);

    // Display process information with calculated times
    printf("\nProcess information:\n");
    displayProcessInfo(p, n);

    return 0;
}
