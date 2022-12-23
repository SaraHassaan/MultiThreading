#include<iostream>
#include<algorithm>
#include<pthread.h>
#include<unistd.h>
using namespace std;

void QuickSort(int*a, int left, int right);
void* QuickSortThread(void*arg);
int partition(int*a, int left, int right);

typedef struct _QsortThreadData{
	int*a;
	int left;
	int right;
}QsortThreadData;

int a_size= 0;
int max_threads;
int n_threads= 0;
pthread_mutex_t mutex_n_threads;


int main(int argc, char *argv[])
{ 
    int a[] = {4,3,7,5,10,2,1};
    
	a_size = sizeof(a)/sizeof(int);
	
	int n_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if(n_cpus > 0){
		max_threads = 2*n_cpus;
	}else{
		max_threads = 8;
	}
	
	pthread_mutex_init(&mutex_n_threads, NULL);
	
	cout <<"before sorting: ";
	for(int i = 0; i < a_size; ++i){
	    cout << a[i] << " ";
	}
	cout << "\n";
	
	QuickSort(a, 0, a_size-1);
	
	cout <<"after sorting: ";
	for(int i = 0; i < a_size; ++i){
	    cout << a[i] << " ";
	}
	cout << "\n";
    	pthread_mutex_destroy(&mutex_n_threads);
	return 0;
}

void QuickSort(int*a, int left, int right){
	QsortThreadData data;
	data.a = a;
	data.left = left;
	data.right = right;
	
	QuickSortThread((void*)&data);
	
}

void* QuickSortThread(void*arg){
	
	QsortThreadData*d = (QsortThreadData*)arg ;
	int left = d->left;
	int right = d->right;
	int*a = d->a;
	
	if(right-left <= 0)return NULL;
	
	int p = partition(a, left, right);
		
	QsortThreadData d1;
	QsortThreadData d2;
	d1.left = left; 
	d1.right = p-1;
	d1.a = a;
	 
	d2.left = p+1; 
	d2.right = right;
	d2.a = a;
	 
	 pthread_mutex_lock(&mutex_n_threads);
	++n_threads;
	pthread_mutex_unlock(&mutex_n_threads);
	
	pthread_t t;
	if(pthread_create(&t, NULL, QuickSortThread, (void*)&d1) != 0 && n_threads >= max_threads){
	    
	    cout << "fail creating a thread \n";	
	    QuickSortThread(&d1);
	}
	QuickSortThread(&d2);
	
	pthread_join(t, NULL);
	
	return NULL;
		
}

int partition(int*a, int left, int right){
	
	int pivot  = a[(rand())%(a_size)];
	
	while(left <right){
		
		if(a[left]<pivot){
			++left;
		}
		if(a[right]>pivot){
			--right;
		}
		swap(a[left], a[right]);
				
	}
	
	return left;
}
