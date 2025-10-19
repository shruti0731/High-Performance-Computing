#include <stdio.h>
#include <omp.h>

int main() {
    int n = 6;
    int arr[] = {1, 2, 3, 4, 5, 6};
    int prefix[n];
    int temp[n];

    for (int i = 0; i < n; i++) {
        prefix[i] = arr[i];
    }

    for (int step = 1; step < n; step *= 2) {
        #pragma omp parallel for
        for (int i = step; i < n; i++) {
            temp[i] = prefix[i] + prefix[i - step];
        }
        for (int i = step; i < n; i++) {
            prefix[i] = temp[i];
        }
    }

    printf("Prefix sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    return 0;
}

