#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sstf_disk_scheduling(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    bool visited[n];
    int seek_times[n];

    // Initialize visited array to false for all requests
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Header for input table
    printf("Input:\n");
    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");

    // Process each request by selecting the shortest seek time next
    printf("Output:\n");
    printf("Current Head Position\tRequested Position\tSeek Time\n");

    for (int i = 0; i < n; i++) {
        int min_seek_time = __INT_MAX__;
        int nearest_request_index = -1;

        // Find the nearest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int seek_time = abs(requests[j] - current_head);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    nearest_request_index = j;
                }
            }
        }

        // Update seek time and move head to the nearest request
        seek_times[i] = min_seek_time;
        visited[nearest_request_index] = true;
        total_seek_time += min_seek_time;

        // Print each step in tabular format
        printf("%d\t\t\t%d\t\t\t%d\n", current_head, requests[nearest_request_index], min_seek_time);

        // Move head to the selected request
        current_head = requests[nearest_request_index];
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

    // Call the SSTF disk scheduling function
    sstf_disk_scheduling(requests, n, initial_head);

    return 0;
}
