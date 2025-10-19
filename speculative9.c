#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int isGoal(const char *s) {
    return strcmp(s, "123456780") == 0;
}
// BFS
int BFS(const char *start) {
    for (long i=0; i<100000000; i++);
    return isGoal(start);
}
// DFS
int DFS(const char *start) {
    for (long i=0; i<50000000; i++);
    return isGoal(start);
}
int main(int argc, char *argv[]) {
    int rank, size, solved = 0;
    char startState[] = "123456780";
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    double start = MPI_Wtime();
    int localSolved = 0;
    if (rank == 0) { // BFS
        if (BFS(startState)) localSolved = 1;
    } else if (rank == 1) { // DFS
        if (DFS(startState)) localSolved = 1;
    }
    // Share results
    MPI_Allreduce(&localSolved, &solved, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    double end = MPI_Wtime();
    if (rank == 0 && solved) printf("Speculative Search: Solution found.\n");
    if (rank == 0) printf("Speculative MPI Time: %f seconds\n", end-start);
    MPI_Finalize();
    return 0;
}
