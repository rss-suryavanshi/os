#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
} Process;

void preemptive_priority_scheduling(Process processes[], int n) {
    int completed = 0, currentTime = 0, min_priority_index;
    int is_completed[MAX_PROCESSES] = {0};

    while (completed != n) {
        min_priority_index = -1;
        int min_priority = INT_MAX;

        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && !is_completed[i] &&
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                min_priority_index = i;
            }
        }

        if (min_priority_index == -1) {
            currentTime++;
            continue;
        }

        // Process selected for execution
        processes[min_priority_index].remaining_time--;
        currentTime++;

        // Check if process is complete
        if (processes[min_priority_index].remaining_time == 0) {
            processes[min_priority_index].finish_time = currentTime;
            processes[min_priority_index].turnaround_time = currentTime - processes[min_priority_index].arrival_time;
            processes[min_priority_index].waiting_time = processes[min_priority_index].turnaround_time - processes[min_priority_index].burst_time;

            is_completed[min_priority_index] = 1;
            completed++;
        }
    }
}

void non_preemptive_priority_scheduling(Process processes[], int n) {
    int completed = 0, currentTime = 0, min_priority_index;
    int is_completed[MAX_PROCESSES] = {0};

    while (completed != n) {
        min_priority_index = -1;
        int min_priority = INT_MAX;

        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && !is_completed[i] &&
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                min_priority_index = i;
            }
        }

        if (min_priority_index == -1) {
            currentTime++;
            continue;
        }

        // Process the selected task to completion
        currentTime += processes[min_priority_index].burst_time;
        processes[min_priority_index].finish_time = currentTime;
        processes[min_priority_index].turnaround_time = currentTime - processes[min_priority_index].arrival_time;
        processes[min_priority_index].waiting_time = processes[min_priority_index].turnaround_time - processes[min_priority_index].burst_time;

        is_completed[min_priority_index] = 1;
        completed++;
    }
}

void print_results(Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].priority, 
               processes[i].finish_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time);
    }
}

int main() {
    int n, mode;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    printf("Select Mode: 1 for Preemptive, 2 for Non-Preemptive: ");
    scanf("%d", &mode);

    if (mode == 1) {
        preemptive_priority_scheduling(processes, n);
        printf("\nPreemptive Priority Scheduling Results:\n");
    } else {
        non_preemptive_priority_scheduling(processes, n);
        printf("\nNon-Preemptive Priority Scheduling Results:\n");
    }

    print_results(processes, n);

    return 0;
}