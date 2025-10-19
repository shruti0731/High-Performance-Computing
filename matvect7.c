#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size, N = 4;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) N = atoi(argv[1]);
    int *A = NULL, *x = NULL, *y = NULL;
    int *localA, *localY;
    int rowsPerProc = N / size;
    if (rank == 0) {
        A = malloc(N * N * sizeof(int));
        x = malloc(N * sizeof(int));
        y = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            x[i] = 1;
            for (int j = 0; j < N; j++) {
                A[i*N+j] = i + j;
            }
        }
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) printf("%d ", A[i*N+j]);
            printf("\n");
        }
        printf("Vector x:\n");
        for (int i = 0; i < N; i++) printf("%d ", x[i]);
        printf("\n");
    }
    if (rank != 0) x = malloc(N * sizeof(int));
    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);


    localA = malloc(rowsPerProc * N * sizeof(int));
    MPI_Scatter(A, rowsPerProc * N, MPI_INT, localA,
                rowsPerProc * N, MPI_INT, 0, MPI_COMM_WORLD);
    localY = malloc(rowsPerProc * sizeof(int));
    for (int i = 0; i < rowsPerProc; i++) {
        localY[i] = 0;
        for (int j = 0; j < N; j++) {
            localY[i] += localA[i*N + j] * x[j];
        }
    }
    //results
    MPI_Gather(localY, rowsPerProc, MPI_INT, y,
               rowsPerProc, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result Vector y:\n");
        for (int i = 0; i < N; i++) printf("%d ", y[i]);
        printf("\n");
    }

    if (rank == 0) { free(A); free(x); free(y); }
    free(localA); free(localY); if (rank != 0) free(x);
    MPI_Finalize();
    return 0;
}
