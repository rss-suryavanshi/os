#include <stdio.h>

int page_faults_FIFO(int pages[], int n, int capacity) {
    int frame[capacity]; // Holds pages in memory
    int page_faults = 0;
    int next_replace = 0; // Keeps track of the FIFO order

    // Initialize frame with -1 to represent empty slots
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

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

        // Page fault occurs if page not found
        if (!found) {
            frame[next_replace] = page;   // Replace the oldest page with the new page
            next_replace = (next_replace + 1) % capacity; // Move to next FIFO position
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

    int faults = page_faults_FIFO(pages, n, capacity);
    printf("Total page faults: %d\n", faults);

    return 0;
}
