#include<stdio.h>
#include<omp.h>
int main(){
	int tnum;
	printf("Enter number of threads: ");
	scanf("%d", &tnum);

	printf("Sequential Print \n");
	for(int i=0;i<tnum;i++)
		printf("Hello world %d \n", i);

	omp_set_num_threads(tnum);
	printf("Parallel Print \n");
	#pragma omp parallel 
	{
		int tid = omp_get_thread_num();
		printf("Hello World %d \n", tid);
	}
	return 0;
}
