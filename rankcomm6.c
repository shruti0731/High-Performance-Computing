#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 5) {
        if (rank == 0)
            fprintf(stderr, "Warning: This program is intended to run with 5 processes. Running with %d.\n", size);
    }

    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    int group_size, group_rank;
    MPI_Group_size(world_group, &group_size);
    MPI_Group_rank(world_group, &group_rank;

    int *members = malloc(sizeof(int) * group_size);
    for (int i = 0; i < group_size; ++i) members[i] = i;

    printf("Process global_rank=%d, group_size=%d, group_rank=%d. Group members: ", rank, group_size, group_rank);
    for (int i = 0; i < group_size; ++i) {
        printf("%d", members[i]);
        if (i < group_size-1) printf(", ");
    }
    printf("\n");

    free(members);
    MPI_Group_free(&world_group);
    MPI_Finalize();
    return 0;
}
