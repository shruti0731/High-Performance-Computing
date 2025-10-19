#include<stdio.h>
#include<omp.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 15

int buffer[BUFFER_SIZE];
int in=0,out=0,count=0;

void produce(int item){
	buffer[in]=item;
	in=(in+1)%BUFFER_SIZE;
	count++;
}

int consume(){
	int item = buffer[out];
	out = (out+1)%BUFFER_SIZE;
	count--;
	return item;
}

int main(){
	omp_set_num_threads(2);
	#pragma omp parallel shared(in,out,count,buffer)
	{
		int thread_id = omp_get_thread_num();
		if(thread_id==0){
			for(int i=1;i<=NUM_ITEMS;i++){
				while(count==BUFFER_SIZE);

				#pragma omp critical
				{
					produce(i);
					printf("\nProducer produced: %d | Buffer count: %d\n",i,count);
				}
			}
		}
		else if(thread_id==1){
			for(int i=1;i<=NUM_ITEMS;i++){
				while(count==0);
				#pragma omp critical
				{
					int item = consume();
					printf("\nConsumer consumed: %d | buffer count: %d",item,count);
				}
			}
		}
	}
	return 0;
}
