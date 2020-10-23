
#define SIZE 1000
#define DIM_GRID 10
#define DIM_BLOCK 100
//kernel function
__global__ void multify(int *a, in*b, int *c) {
    //a is the 1K x 1K matrix, b is 1K vector, c is 1K vector too
    int row = blockIdx.y*blockDim.y + threadIdx.y;
    int col = blockIdx.x*blockDim.x + threadIdx.x;
    float c_val = 0;
    for (int tileId=0; tileId<(DIM_GRID; tileId++)) {
        __shared__ tile_b[SIZE/DIM_GRID];
        tile_b = b[(tileId*threadIdx.x)*SIZE+col];
        __syncthreads();
        for (int k=0; k<SIZE; k++) {
            c_val+=a[threadIdx.y][k]*tile_b[k][threadIdx.x];
        }
        __syncthreads();
    }
    c[row*SIZE+col] = c_val;
}


//CUDA code on the host side
int main() {
    //initialize a, b, c
    int *a = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int *b = (int*)malloc(sizeof(int)*SIZE);
    int *c = (int*)malloc(sizeof(int)*SIZE);

    int *gpu_a, *gpu_b, *gpu_c;
    cudamalloc((void**)&gpu_a, sizeof(int)*SIZE*SIZE);
    cudamalloc((void**)&gpu_b, sizeof(int)*SIZE);
    cudamalloc((void**)&gpu_c, sizeof(int)*SIZE);

    cudaMemcpy(gpu_a, a, sizeof(int)*SIZE*SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_b, b, sizeof(int)*SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_c, c, sizeof(int)*SIZE, cudaMemcpyHostToDevice);

    dim3 dimGrid(DIM_GRID);
    dim3 dimBlock(DIM_BLOCK);
    multify<<<dimGrid, dimBlock>>>(gpu_a, gpu_b, gpu_c);
    cudaMemcpy(c, gpu_c, sizeof(int)*SIZE, cudaMemcpyDeviceToHost); 
}