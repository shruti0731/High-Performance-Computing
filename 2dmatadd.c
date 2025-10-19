#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void add_matrices(int N, int num_threads) {
    int i, j;
    // Dynamically allocate matrices A, B, and C
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }
    // Initialize matrices with simple values
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    // Set the number of threads
    omp_set_num_threads(num_threads);
    // Start timer
    double start_time = omp_get_wtime();
    // Parallelize the matrix addition.
    #pragma omp parallel for collapse(2)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Stop timer
    double end_time = omp_get_wtime();
    // Calculate and print the runtime
    double runtime = end_time - start_time;
    printf("Matrix Size: %d, Threads: %d, Runtime: %f seconds\n", N, num_threads, runtime);
}

int main() {
    int matrix_sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
    int num_threads[] = {1, 2, 4, 8};
    int num_thread_counts = sizeof(num_threads) / sizeof(num_threads[0]);
    int s, t;

    printf("--- Matrix Addition Performance Test ---\n");

    for (s = 0; s < num_sizes; s++) {
        for (t = 0; t < num_thread_counts; t++) {
            add_matrices(matrix_sizes[s], num_threads[t]);
        }
        printf("--------------------------------------\n");
    }
    return 0;
}
