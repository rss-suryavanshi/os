#include <stdio.h>

int find_optimal(int pages[], int n, int frame[], int capacity, int current_index) {
    int farthest = current_index, pos = -1;

    // Find the page that won't be used for the longest time in the future
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = current_index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If this page isn't used again in the future
        if (j == n) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}
 
int page_faults_optimal(int pages[], int n, int capacity) {
    int frame[capacity]; // Holds pages in memory
    int page_faults = 0;

    // Initialize frame with -1 to represent empty slots
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1; // Page is already in the frame
                break;
            }
        }

        // If the page is not in the frame, a page fault occurs
        if (!found) {
            int pos = -1;

            // Check if there is an empty slot in the frame
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty slot, use the optimal replacement policy
            if (pos == -1) {
                pos = find_optimal(pages, n, frame, capacity, i + 1);
            }

            // Replace the page at the optimal position with the new page
            frame[pos] = page;
            page_faults++;
        }

        // Display current frame contents
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    return page_faults;
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string (page numbers): ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    int faults = page_faults_optimal(pages, n, capacity);
    printf("Total page faults: %d\n", faults);

    return 0;
}
