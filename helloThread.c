#include<stdio.h>
#include<omp.h>
int main(){
	#pragma omp parallel
	{
		printf("Hello world with threads.. \n");
	}
	return 0;
}
