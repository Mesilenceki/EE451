#include <stdlib.h>
#include <stdio.h>
#include <cublas.h>
#include <time.h>

#define DIM_GRID 32
#define DIM_BLOCK 32
#define SIZE 1024

__global__ void matrix_multify(int *a, int *b, int*c) {
    unsigned int row = blockIdx.y*blockDim.y + threadIdx.y;
    unsigned int col = blockIdx.x*blockDim.x + threadIdx.x;
    if ((row < SIZE)&&(col < SIZE)) {
        int value_C = 0;
        for (int tileId=0; tileId<(SIZE/DIM_GRID); tileId++) {
            __shared__ int a_tile[SIZE/DIM_GRID][SIZE/DIM_GRID];
            __shared__ int b_tile[SIZE/DIM_GRID][SIZE/DIM_GRID];
            //loading the a and b tiles into shared memory
            a_tile[threadIdx.y][threadIdx.x] = a[row*SIZE+(tileId*SIZE/DIM_GRID+threadIdx.x)];
            b_tile[threadIdx.y][threadIdx.x] = b[(tileId*SIZE/DIM_GRID+threadIdx.y)*SIZE+col];
            __syncthreads();
            for (int k=0; k<SIZE/DIM_GRID; k++) {
                value_C+=a_tile[threadIdx.y][k]*b_tile[k][threadIdx.x];
            }
            __syncthreads();
        }
        c[row*SIZE+col] = value_C;
    }
}
int main() {
    int i;
    struct timespec start, stop;
    double time;
    int *a = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int *b = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int *c = (int*)malloc(sizeof(int)*SIZE*SIZE);

    for (i=0; i<SIZE*SIZE; i++) {
        a[i] = 1;
        b[i] = 2;
        c[i] = 0;
    }

    int *a_gpu, *b_gpu, *c_gpu;
    cudaMalloc((void**)&a_gpu, sizeof(int)*SIZE*SIZE);
    cudaMalloc((void**)&b_gpu, sizeof(int)*SIZE*SIZE);
    cudaMalloc((void**)&c_gpu, sizeof(int)*SIZE*SIZE);

    cudaMemcpy(a_gpu, a, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(b_gpu, b, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(c_gpu, c, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);

    dim3 dimBlock(DIM_BLOCK, DIM_BLOCK);
    dim3 dimGrid(DIM_GRID, DIM_GRID);
    //start our cuda program
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
    }
    matrix_multify<<<dimGrid, dimBlock>>>(a_gpu, b_gpu, c_gpu);
    cudaMemcpy(c, c_gpu, sizeof(int)*SIZE*SIZE, cudaMemcpyDeviceToHost);

    if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
    }
    time = (stop.tv_sec - start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1e9;
    printf("time is %f ns\n", time*1e9);
    printf("c[451][451] is %d\n", c[451*SIZE+451]);

    free(a);
    free(b);
    free(c);
    cudaFree(a_gpu);
    cudaFree(b_gpu);
    cudaFree(c_gpu);
    return 0;
}