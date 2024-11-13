#include <stdio.h>
#include <stdlib.h>

void fcfs_disk_scheduling(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    int seek_times[n];

    // Header for input table
    printf("Input:\n");
    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");

    // Process each request in FCFS order
    printf("Output:\n");
    printf("Current Head Position\tRequested Position\tSeek Time\n");
    
    for (int i = 0; i < n; i++) {
        int seek_time = abs(requests[i] - current_head);
        seek_times[i] = seek_time;
        total_seek_time += seek_time;
        
        printf("%d\t\t\t%d\t\t\t%d\n", current_head, requests[i], seek_time);

        current_head = requests[i];
    }

    // Print total seek time
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, initial_head;

    // Input the initial head position
    printf("Enter initial head position: ");
    scanf("%d", &initial_head);

    // Input the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    // Input the disk requests sequence
    printf("Enter the disk requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Call the FCFS disk scheduling function
    fcfs_disk_scheduling(requests, n, initial_head);

    return 0;
}
