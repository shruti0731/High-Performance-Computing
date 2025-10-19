#include<stdio.h>
#include<omp.h>

long fibo(int n){
	if(n<2) return n;
	long x,y;
	#pragma omp task shared(x)
	x=fibo(n-1);
	#pragma omp task shared(y)
	y=fibo(n-2);
	#pragma omp taskwait
	return x+y;
}

int main(){
	int n;
	printf("Enter number:");
	scanf("%d",&n);
	long res;
	double srt,end;
	srt=omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		res = fibo(n);
	}
	end = omp_get_wtime();
	printf("\nFibonacci Series:%ld\n",res);
	printf("Time required:%f\n",end-srt);
	return 0;
}
