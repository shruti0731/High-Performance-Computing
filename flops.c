#include <stdio.h>
#include <omp.h>

int main() {
    double start_time, end_time;
    double a = 1.5, b = 2.5, c;
    long long int iterations = 1000000000; // 1 billion
    int i;

    start_time = omp_get_wtime();

    for(i = 0; i < iterations; i++) {
        c = a * b + a / b;  // 2 floating point operations
    }

    end_time = omp_get_wtime();

    double total_time = end_time - start_time;
    double flops = (2.0 * iterations) / total_time;

    printf("Time taken: %f seconds\n", total_time);
    printf("Estimated FLOPS: %.2f MFLOPS\n", flops / 1e6);

    return 0;
}
