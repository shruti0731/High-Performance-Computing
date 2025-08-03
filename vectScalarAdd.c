#include <stdio.h>
#include <omp.h>
int main() {
    int n = 100; 
    int scalar = 5;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
        a[i] = i;

    double start = omp_get_wtime();
    // Parallel region
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        b[i] = a[i] + scalar;
    }
    printf("Vector-scalar addition result :\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d] = %d\n", i, b[i]);
    }
    double end = omp_get_wtime();
    printf("Vector-scalar addition completed in %f seconds\n", end - start);
    return 0;
}
