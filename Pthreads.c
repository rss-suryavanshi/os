#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 3  // Define the size of the matrix (for simplicity, a 3x3 matrix)

int A[MAX][MAX]; // Matrix A
int B[MAX][MAX]; // Matrix B
int result_add[MAX][MAX]; // Result matrix for addition
int result_mul[MAX][MAX]; // Result matrix for multiplication

// Structure to hold parameters for each thread
typedef struct {
    int row;
    int col;
} MatrixPos;

// Function for each thread to calculate a single element in the addition result matrix
void *matrix_add(void *param) {
    MatrixPos *pos = (MatrixPos *)param;
    int row = pos->row;
    int col = pos->col;

    // Calculate the element of the result matrix
    result_add[row][col] = A[row][col] + B[row][col];

    pthread_exit(0);
}

// Function for each thread to calculate a single element in the multiplication result matrix
void *matrix_multiply(void *param) {
    MatrixPos *pos = (MatrixPos *)param;
    int row = pos->row;
    int col = pos->col;

    result_mul[row][col] = 0;
    for (int k = 0; k < MAX; k++) {
        result_mul[row][col] += A[row][k] * B[k][col];
    }

    pthread_exit(0);
}

int main() {
    // Initialize matrices A and B with example values
    printf("Enter elements of 3x3 matrix A:\n");
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of 3x3 matrix B:\n");
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            scanf("%d", &B[i][j]);

    // Matrix addition with threads
    pthread_t threads_add[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            MatrixPos *pos = (MatrixPos *)malloc(sizeof(MatrixPos));
            pos->row = i;
            pos->col = j;
            pthread_create(&threads_add[i][j], NULL, matrix_add, (void *)pos);
        }
    }

    // Join addition threads
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads_add[i][j], NULL);
        }
    }

    // Display addition result
    printf("\nResult of matrix addition:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", result_add[i][j]);
        }
        printf("\n");
    }

    // Matrix multiplication with threads
    pthread_t threads_mul[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            MatrixPos *pos = (MatrixPos *)malloc(sizeof(MatrixPos));
            pos->row = i;
            pos->col = j;
            pthread_create(&threads_mul[i][j], NULL, matrix_multiply, (void *)pos);
        }
    }

    // Join multiplication threads
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads_mul[i][j], NULL);
        }
    }

    // Display multiplication result
    printf("\nResult of matrix multiplication:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", result_mul[i][j]);
        }
        printf("\n");
    }

    return 0;
}
