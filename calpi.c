#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 100000000; 
    double step = 1.0 / (double)num_steps;

    int thread_counts[] = {1, 2, 4, 8};
    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int t = 0; t < num_configs; t++) {
        int num_threads = thread_counts[t];
        omp_set_num_threads(num_threads);

        double sum = 0.0;
        double start_time = omp_get_wtime();

        #pragma omp parallel
        {
            double x;
            double local_sum = 0.0;
            #pragma omp for
            for (int i = 0; i < num_steps; i++) {
                x = (i + 0.5) * step;
                local_sum += 4.0 / (1.0 + x * x);
            }
            #pragma omp atomic
            sum += local_sum;
        }
        double pi = step * sum;
        double end_time = omp_get_wtime();
        printf("Threads: %d | Pi = %.15f | Time = %.6f seconds\n", num_threads, pi, end_time - start_time);
    }
    return 0;
}
