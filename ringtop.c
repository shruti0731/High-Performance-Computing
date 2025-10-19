#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int left = (rank - 1 + size) % size;
    int right = (rank + 1) % size;
    int send_to_right = rank;
   int recv_from_left = -1;
    if (rank % 2 == 0) {
        MPI_Send(&send_to_right, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_from_left, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&recv_from_left, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&send_to_right, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    }

    printf("Rank %d sent %d to right=%d, received %d from left=%d\n",
           rank, send_to_right, right, recv_from_left, left);

    MPI_Finalize();
    return 0;
}

