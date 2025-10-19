#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure we have exactly 2 processes
    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "This program requires exactly 2 processes. Running with %d.\n", size);
        }
        MPI_Finalize();
        return 1;
    }

    int n = 10; // default array size
    if (rank == 0 && argc > 1) n = atoi(argv[1]);

    // Broadcast n to both processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int half = n / 2;
    int remainder = n - half;
    int *A = NULL;
    if (rank == 0) {
        A = malloc(sizeof(int) * n);
        for (int i = 0; i < n; ++i) A[i] = i + 1;
        printf("Array A (n=%d): ", n);
        for (int i = 0; i < n; ++i) printf("%d ", A[i]);
        printf("\n");
    }

    if (rank == 0) {
        int sum0 = 0;
        for (int i = 0; i < half; ++i) sum0 += A[i];

        // Send second half to P1
        MPI_Send(A + half, remainder, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Receive partial sum from P1
        int sum1 = 0;
        MPI_Recv(&sum1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("P0 sum = %d, P1 sum = %d, Total sum = %d\n", sum0, sum1, sum0 + sum1);
        free(A);
    } else { // rank 1
        int *buf = malloc(sizeof(int) * remainder);
        MPI_Recv(buf, remainder, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int sum1 = 0;
        for (int i = 0; i < remainder; ++i) sum1 += buf[i];

        MPI_Send(&sum1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        free(buf);
    }

    MPI_Finalize();
    return 0;
}



