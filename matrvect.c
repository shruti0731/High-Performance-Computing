#include <stdio.h>
#include <omp.h>

#define N 3

int main() {
    int A[N][N], x[N], y[N];
    int i, j;

    for (i = 0; i < N; i++) {
        x[i] = i + 1;
        y[i] = 0;
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }
    #pragma omp parallel for private(j) shared(A, x, y)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    printf("Result Vector (y):\n");
    for (i = 0; i < N; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    return 0;
}
