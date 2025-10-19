#include <stdio.h>
#include <string.h>
#include <time.h>
#define N 6
#define WORD "CAT"
char grid[N][N] = {
    {'C','A','T','X','Y','Z'},
    {'X','Y','Z','C','A','T'},
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
int main() {
    clock_t start, end;
    int foundCount = 0;

    start = clock();
    for (int row=0; row<N; row++) {
        for (int col=0; col<N; col++) {
            if (grid[row][col] == WORD[0]) {
                int dirs[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
                for (int d=0; d<8; d++) {
                    if (searchWord(row, col, dirs[d][0], dirs[d][1], WORD)) {
                        foundCount++;
                    }
                }
            }
        }
    }
    end = clock();

    printf("Sequential: Word '%s' found %d times.\n", WORD, foundCount);
    printf("Sequential Time: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
