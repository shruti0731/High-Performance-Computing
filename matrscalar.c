#include <stdio.h>
#include <omp.h>

#define N 3

int main() {
    int A[N][N], B[N][N];
    int i, j;
    int scalar = 5;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }
    #pragma omp parallel for private(j) shared(A, B)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = scalar * A[i][j];
        }
    }
    printf("Result Matrix (B):\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}
