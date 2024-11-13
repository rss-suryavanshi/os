#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
} Process;

void round_robin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0;
    int is_completed[MAX_PROCESSES] = {0};

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                // Check if the process can complete within the quantum
                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].finish_time = time;
                    processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    is_completed[i] = 1;
                    completed++;
                } else {
                    // Process requires more than the quantum
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                }
            }
        }
    }
}

void print_results(Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].finish_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time);
    }
}

int main() {
    int n, quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    round_robin(processes, n, quantum);
    print_results(processes, n);

    return 0;
}
