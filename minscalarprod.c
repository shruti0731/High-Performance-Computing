#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// Function to compare two integers for ascending sort
int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
// Function to compare two integers for descending sort
int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}
int main() {
    int n = 10000; // Vector size
    int i;
    long long dot_product = 0;
    // Dynamically allocate memory for the vectors
    int *v1 = (int *)malloc(n * sizeof(int));
    int *v2 = (int *)malloc(n * sizeof(int));
    // Seed the random number generator
    srand(12345);
    for (i = 0; i < n; i++) {
        v1[i] = rand() % 100;
        v2[i] = rand() % 100;
    }

    // Sort vector 1 in ascending order
    qsort(v1, n, sizeof(int), compare_asc);

    // Sort vector 2 in descending order
    qsort(v2, n, sizeof(int), compare_desc);
    #pragma omp parallel for reduction(+:dot_product)
    for (i = 0; i < n; i++) {
        dot_product += (long long)v1[i] * v2[i];
    }
    printf("The minimum scalar product of the two vectors is: %lld\n", dot_product);
    return 0;
}
