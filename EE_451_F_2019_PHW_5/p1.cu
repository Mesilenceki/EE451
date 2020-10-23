#include <stdlib.h>
#include <stdio.h>
#include <cublas.h>
#include <time.h>

#define SIZE 1024
#define GRID_SIZE 64;
#define BLOCK_SIZE 16;

__global__ void matrix_mupltify(int *a, int *b, int *c) {
    int row = blockIdx.y*blockDim.y + threadIdx.y;
    int col = blockIdx.x*blockDim.x + threadIdx.x;
    int c_val = 0;
    for (int k=0; k<SIZE; k++) {
        c[row*SIZE+col] += a[row*SIZE+k]*b[k*SIZE+col];
    }
    c[row*SIZE+col] = c_val;
}

int main() {
    int i=0;
    
    int *a = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int *b = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int *c = (int*)malloc(sizeof(int)*SIZE*SIZE);

    for (i=0; i<SIZE*SIZE; i++) {
        a[i] = 1;
        b[i] = 2;
    }

    int *gpu_a, *gpu_b, *gpu_c;
    cudaMalloc((void**)&gpu_a, sizeof(int)*SIZE*SIZE);
    cudaMalloc((void**)&gpu_b, sizeof(int)*SIZE*SIZE);
    cudaMalloc((void**)&gpu_c, sizeof(int)*SIZE*SIZE);

    cudaMemcpy(gpu_a, a, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_b, b, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);
    
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid(GRID_SIZE, GRID_SIZE);
    //start our cuda program
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
    }
    
    matrix_mupltify<<<dimGrid, dimBlock>>>(gpu_a, gpu_b, gpu_c);
    cudaMemcpy(c, gpu_c, sizeof(int)*SIZE*SIZE, cudaMemcpyDeviceToHost);
    
    if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
    }
    time = (stop.tv_sec - start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1e9;
    printf("time is %f ns\n", time*1e9);
    printf("c[451][451]=%d\n", c[451*SIZE+451]);

    free(a);
    free(b);
    free(c);
    cudaFree(gpu_a);
    cudaFree(gpu_b);
    cudaFree(gpu_c);
    return 0;
}