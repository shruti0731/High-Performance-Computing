#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size, N = 4;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) N = atoi(argv[1]);
    int *A = NULL, *B = NULL, *C = NULL;
    int *localA, *localC;

    int rowsPerProc = N / size;

    if (rank == 0) {
        A = malloc(N * N * sizeof(int));
        B = malloc(N * N * sizeof(int));
        C = malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i*N+j] = i + j;
                B[i*N+j] = i == j ? 1 : 0;
            }
        }
        printf("Matrix A:\n");
        for (int i=0; i<N; i++){ for (int j=0;j<N;j++) printf("%d ",A[i*N+j]); printf("\n"); }
        printf("Matrix B:\n");
        for (int i=0; i<N; i++){ for (int j=0;j<N;j++) printf("%d ",B[i*N+j]); printf("\n"); }
    }

    if (rank != 0) B = malloc(N * N * sizeof(int));
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    localA = malloc(rowsPerProc * N * sizeof(int));
    MPI_Scatter(A, rowsPerProc*N, MPI_INT, localA,
                rowsPerProc*N, MPI_INT, 0, MPI_COMM_WORLD);

    localC = malloc(rowsPerProc * N * sizeof(int));
    for (int i = 0; i < rowsPerProc; i++) {
        for (int j = 0; j < N; j++) {
            localC[i*N+j] = 0;
            for (int k = 0; k < N; k++) {
                localC[i*N+j] += localA[i*N+k] * B[k*N+j];
            }
        }
    }
    MPI_Gather(localC, rowsPerProc*N, MPI_INT, C,
               rowsPerProc*N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result Matrix C:\n");
        for (int i=0; i<N; i++){ for (int j=0;j<N;j++) printf("%d ",C[i*N+j]); printf("\n"); }
    }

    if (rank==0){ free(A); free(B); free(C);}
    free(localA); free(localC); if (rank!=0) free(B);
    MPI_Finalize();
    return 0;
}
