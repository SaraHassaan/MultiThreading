#include<pthread.h>
#include<iostream>
using namespace std;

int a[] = { 1,2,3,4,5,5 ,1,2};

typedef struct _thread_data{
	
	int sum;
	int index;
	int limit;
}thread_data;

void*SumArray(void*arg){
	thread_data *data = (thread_data*)arg;
	data->sum = 0;
	
	for(int i = 0; i< data->limit; ++i){
		
			data->sum += a[i+data->index];//index consider as offest
	}

	return (void*)arg;
}
int main(int argc, char *argv[])
{
	const int SIZE = sizeof(a)/sizeof(int);
	thread_data d1;
	thread_data d2;
	
	d1.index = 0;
	d1.limit = SIZE/2;
	
	d2.index = SIZE/2;
	d2.limit = SIZE - (SIZE/2);
	
	
	pthread_t t1,t2;
	if(pthread_create(&t1,NULL,SumArray,(void*)&d1)!=0){
		
		return 1;
	}
	
	if(pthread_create(&t2,NULL,SumArray,(void*)&d2)!=0){
		
		return 3;
	}
	thread_data *p1 = &d1;
	thread_data *p2 = &d2;
	
	if(pthread_join(t1,(void**)&p1)!=0){
		return 2;
	}
	
	if(pthread_join(t2,(void**)&p2)!=0){
		return 4;
	}
	
	int total_sum = d1.sum + d2.sum;
	
	cout << total_sum;
	
	return 0;
}
