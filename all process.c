#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// Function to calculate the sum of even numbers in an array
int sum_of_even(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

// Function to calculate the sum of odd numbers in an array
int sum_of_odd(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);
    int choice;

    printf("Choose an option:\n");
    printf("1. Calculate sum of even numbers (Parent process)\n");
    printf("2. Calculate sum of odd numbers (Child process)\n");
    printf("3. Demonstrate both zombie and orphan processes\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            // Calculate sum of even numbers in the parent process
            int even_sum = sum_of_even(arr, size);
            printf("Sum of even numbers: %d\n", even_sum);
            break;
        }
        case 2: {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
                // Child process to calculate sum of odd numbers
                int odd_sum = sum_of_odd(arr, size);
                printf("Sum of odd numbers (Child Process): %d\n", odd_sum);
                exit(0); // Exiting immediately
            } else {
                // Parent waits for child to finish
                wait(NULL);
            }
            break;
        }
        case 3: {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
                // Child process calculates sum of odd numbers
                int odd_sum = sum_of_odd(arr, size);
                printf("Sum of odd numbers (Child Process): %d\n", odd_sum);

                // Demonstrate orphan process by sleeping briefly
                sleep(1);
                printf("Child process (Orphan) executing after parent exits.\n");
                exit(0); // Child exits
            } else {
                // Parent calculates sum of even numbers
                int even_sum = sum_of_even(arr, size);
                printf("Sum of even numbers (Parent Process): %d\n", even_sum);

                // Demonstrate zombie process
                sleep(1);
                printf("Zombie process demonstration completed.\n");

                // Wait to clean up zombie process
                wait(NULL);

                printf("Parent process exiting, making child an orphan.\n");
                sleep(2); // Parent exits, making child an orphan briefly
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
