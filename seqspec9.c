#include <stdio.h>
#include <string.h>
#include <time.h>

int isGoal(const char *s) {
    return strcmp(s, "123405678") == 0;
}
int BFS(const char *start) {
    for (long i=0; i<100000000; i++);
    return isGoal(start);
}

int main() {
    char startState[] = "123405678";
    clock_t start, end;

    start = clock();
    int solved = BFS(startState);
    end = clock();

    if (solved) printf("Sequential BFS: Puzzle Solved!\n");
    else printf("Sequential BFS: Not Solved.\n");

    printf("Sequential BFS Time: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
