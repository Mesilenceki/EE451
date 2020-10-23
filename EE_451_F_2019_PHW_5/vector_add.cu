#include <stdlib.h>
#include <stdio.h>
#include <cublas.h>
#include <time.h>

#define size 65536


__global__ void vector_add(int *a, int *b, int *c){
	int my_id;
	my_id = blockIdx.x*blockDim.x + threadIdx.x;	
	c[my_id] = a[my_id] + b[my_id];  
}

int main(){		
    int i;
    int *a = (int*)malloc(sizeof(int)*size);          
    int *b = (int*)malloc(sizeof(int)*size);
    int *c = (int*)malloc(sizeof(int)*size);           	
	
    for(i=0; i<size; i++){
        a[i]=1;
        b[i]=2;
  	}
    int *gpu_a, *gpu_b, *gpu_c;
    cudaMalloc((void**)&gpu_a, sizeof(int)*size);
    cudaMalloc((void**)&gpu_b, sizeof(int)*size);
    cudaMalloc((void**)&gpu_c, sizeof(int)*size);
		
    struct timespec start, stop;
    double time;
	  
	  
    cudaMemcpy(gpu_a, a, sizeof(int)*size, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_b, b, sizeof(int)*size, cudaMemcpyHostToDevice);
		
    dim3 dimGrid(64);
    dim3 dimBlock(1024);
		
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) { perror( "clock gettime" );}
    vector_add<<<dimGrid, dimBlock>>>(gpu_a, gpu_b, gpu_c);
    cudaMemcpy(c, gpu_c, sizeof(int)*size, cudaMemcpyDeviceToHost);
		
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror( "clock gettime" );}
    time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    printf("time is %f ns\n", time*1e9);
		
    for(i=0; i<256; i++)
        printf("c[%d]=%d ", i, c[i]);
  	
    free(a);
    free(b);
    free(c);
    cudaFree(gpu_a);
    cudaFree(gpu_b);
    cudaFree(gpu_c);
    return 0;
}	
