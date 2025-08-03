#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const long long num_operations = 1000000000;
    double a = 1.5, b = 2.5, c;
    
    clock_t start = clock();

    for (long long i = 0; i < num_operations; i++) {
        c = a * b + a; // 2 floating-point operations
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    double flops = (2.0 * num_operations) / time_taken;

    printf("Time taken: %f seconds\n", time_taken);
    printf("Estimated FLOPS: %f\n", flops);

    return 0;
}

