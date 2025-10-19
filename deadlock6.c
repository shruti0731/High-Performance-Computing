#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) fprintf(stderr, "Deadlock example requires at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    int other = (rank == 0) ? 1 : 0;
    int sendbuf = rank;
    int recvbuf = -1;

    printf("Rank %d: calling MPI_Send (this will block until matching receive) to %d\n", rank, other);
    fflush(stdout);

    MPI_Send(&sendbuf, 1, MPI_INT, other, 0, MPI_COMM_WORLD);

    MPI_Recv(&recvbuf, 1, MPI_INT, other, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Rank %d: received %d from %d\n", rank, recvbuf, other);

    MPI_Finalize();
    return 0;
}
