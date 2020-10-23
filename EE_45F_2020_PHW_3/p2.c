#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define		size	   16*1024*1024
#define     num_of_threads 2

omp_set_num_threads(num_of_threads);

void quickSort(int *array, int start, int end){
    // you quick sort function goes here
	if (start < end) {
		int pivot = partition(array, start, end)
		quickSort(array, start, pivot-1);
		quickSort(array, pivot+1, end);
	} 
}

int partition(int *array, int start, int end) {
	int pivot = array[end];
	int i = start-1;

	for (int j = start; j<=end-1; j++) {
		if (array[j]<=pivot) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i+1], &array[end]);
	return (i+1);
}

void quickSortPara(int *array, int start, int end) {
	if (start < end) {
		int pivot;
		#pragma omp parallel default(array, start, end) private(pivot) 
		{	
			#pragma omp sections nowait
			{
				pivot = partitionPara(array, start, end);

				#pragma omp section
				quickSortPara(array, start, pivot-1);
				
				#pragma omp section
				quickSortPara(array, pivot+1, end);
			}
		}
		
	}
}

int partitionPara(int *array, int start, int end) {
	int pivot = array[rand()%size];

	for (int j = start; j<=end-1; j++) {
		if (array[j]<=pivot) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i+1], &array[end]);
	return (i+1);
}

void swap(int *a, int *b) {
	int tmp = *a;
	int *a = *b;
	int*b = tmp;
}

int main(void){
	int i, j, tmp;
	struct timespec start, stop; 
	double exe_time;
	srand(time(NULL)); 
	int * m = (int *) malloc (sizeof(int)*size);
	for(i=0; i<size; i++){
		m[i]=size-i;
	}
	
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	////////**********Your code goes here***************//
	quickSort(m, 0, size-1);
	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	
	for(i=0;i<16;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);	


	for(i=0; i<size; i++){
		m[i]=size-i;
	}

	/* OpenMP implementation here */
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	////////**********Your code goes here***************//
	quickSortPara(m, 0, size-1);
	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	
	for(i=0;i<16;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);	
}	