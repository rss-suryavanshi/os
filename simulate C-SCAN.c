#include <stdio.h>
#include <stdlib.h>

void cscan_disk_scheduling(int requests[], int n, int initial_head, int disk_size) {
    int total_seek_time = 0;
    int current_head = initial_head;
    int sorted_requests[n + 2];  // Including the boundary values (0 and disk_size-1)
    int i, j, k = 0;

    // Add boundary requests (0 and disk_size - 1) to the requests array
    sorted_requests[0] = 0;
    sorted_requests[1] = disk_size - 1;
    k = 2;

    // Copy all requests to sorted_requests array
    for (i = 0; i < n; i++) {
        sorted_requests[k++] = requests[i];
    }

    // Sort all requests, including boundaries
    for (i = 0; i < k - 1; i++) {
        for (j = i + 1; j < k; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Find the starting index based on the initial head position
    int start_index = 0;
    for (i = 0; i < k; i++) {
        if (sorted_requests[i] >= initial_head) {
            start_index = i;
            break;
        }
    }

    printf("Input:\n");
    printf("Request Sequence: ");
    for (i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");

    printf("Output:\n");
    printf("Current Head Position\tRequested Position\tSeek Time\n");

    // First, service requests from initial head position to end of disk
    for (i = start_index; i < k; i++) {
        int seek_time = abs(sorted_requests[i] - current_head);
        total_seek_time += seek_time;
        printf("%d\t\t\t%d\t\t\t%d\n", current_head, sorted_requests[i], seek_time);
        current_head = sorted_requests[i];
    }

    // Move to the beginning of the disk after reaching the end
    if (current_head != 0) {
        int seek_time = abs(disk_size - 1 - current_head);
        total_seek_time += seek_time;
        printf("%d\t\t\t%d\t\t\t%d\n", current_head, 0, seek_time);
        current_head = 0;
    }

    // Continue servicing requests from start of disk to the initial head position
    for (i = 0; i < start_index; i++) {
        int seek_time = abs(sorted_requests[i] - current_head);
        total_seek_time += seek_time;
        printf("%d\t\t\t%d\t\t\t%d\n", current_head, sorted_requests[i], seek_time);
        current_head = sorted_requests[i];
    }

    // Print total seek time
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, initial_head, disk_size;

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &initial_head);

    // Input disk size (assuming track numbers from 0 to disk_size - 1)
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    // Input the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    // Input the disk requests sequence
    printf("Enter the disk requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Call the C-SCAN disk scheduling function
    cscan_disk_scheduling(requests, n, initial_head, disk_size);

    return 0;
}
