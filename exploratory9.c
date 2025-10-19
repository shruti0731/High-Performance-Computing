#include <mpi.h>
#include <stdio.h>
#include <string.h>
#define N 6
#define WORD "BAT"

char grid[N][N] = {
    {'C','A','T','X','Y','Z'},
    {'B','A','T','E','A','T'},
    {'A','B','C','D','E','F'},
    {'T','A','C','T','A','C'},
    {'C','A','T','C','A','T'},
    {'X','Y','Z','X','Y','Z'}
};

int searchWord(int row, int col, int dx, int dy, const char *word) {
    int len = strlen(word);
    for (int i=0; i<len; i++) {
        int r = row + i*dx;
        int c = col + i*dy;
        if (r<0 || r>=N || c<0 || c>=N || grid[r][c] != word[i]) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    double start, end;
    int localCount = 0, globalCount = 0;

    // Divide rows among processes
    int rowsPerProc = N / size;
    int startRow = rank * rowsPerProc;
    int endRow = (rank == size-1) ? N : startRow + rowsPerProc;

    start = MPI_Wtime();
    for (int row=startRow; row<endRow; row++) {
        for (int col=0; col<N; col++) {
            if (grid[row][col] == WORD[0]) {
                int dirs[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
                for (int d=0; d<8; d++) {
                    if (searchWord(row, col, dirs[d][0], dirs[d][1], WORD)) {
                        localCount++;
                    }
                }
            }
        }
    }
    end = MPI_Wtime();

    MPI_Reduce(&localCount, &globalCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Word '%s' found %d times in parallel MPI search.\n", WORD, globalCount);
        printf("Parallel MPI Time: %f seconds\n", end-start);
    }

    MPI_Finalize();
    return 0;
}
