#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void perform_scalar_addition(int n, int scalar, int chunk_size, const char* schedule_type) {
    int i;
    int *v = (int *)malloc(n * sizeof(int));
    // Initialize vector
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
    double start_time = omp_get_wtime();
    // Use schedule clause based on function parameter
    if (strcmp(schedule_type, "STATIC") == 0) {
        // i. STATIC schedule with specified chunk size
        #pragma omp parallel for schedule(static, chunk_size)
        for (i = 0; i < n; i++) {
            v[i] += scalar;
        }
    } else if (strcmp(schedule_type, "DYNAMIC") == 0) {
        // ii. DYNAMIC schedule with specified chunk size
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (i = 0; i < n; i++) {
            v[i] += scalar;
        }
    } else {
        printf("Invalid schedule type: %s\n", schedule_type);
        free(v);
        return;
    }
    double end_time = omp_get_wtime();
    double runtime = end_time - start_time;
    printf("Schedule: %s, Chunk Size: %d, Runtime: %f seconds\n", schedule_type, chunk_size, runtime);
    free(v);
}
void demonstrate_nowait() {
    int n = 200;
    int i;
    int *a = (int *)malloc(n * sizeof(int));

    // Initialize vector
    for (i = 0; i < n; i++) {
        a[i] = i;
    }
    printf("\n--- Demonstrating nowait clause ---\n");
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < n; i++) {
            a[i] += 10;
        }
        printf("Thread %d is moving on to the next task.\n", omp_get_thread_num());
    }
    printf("--- nowait demonstration finished ---\n"); }

int main() {
    int n = 200;
    int scalar = 5;
    printf("--- Scalar Addition Performance with Different Schedules ---\n");
    perform_scalar_addition(n, scalar, 1, "STATIC");
    perform_scalar_addition(n, scalar, 10, "STATIC");
    perform_scalar_addition(n, scalar, 50, "STATIC");
    perform_scalar_addition(n, scalar, 200, "STATIC");
    printf("----------------------------------------------------------\n");
    perform_scalar_addition(n, scalar, 1, "DYNAMIC");
    perform_scalar_addition(n, scalar, 10, "DYNAMIC");
    perform_scalar_addition(n, scalar, 50, "DYNAMIC");
    perform_scalar_addition(n, scalar, 200, "DYNAMIC");
    //nowait clause
    demonstrate_nowait();
    return 0;
}
