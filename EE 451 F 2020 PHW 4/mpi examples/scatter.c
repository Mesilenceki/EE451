#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int b=0;
    int a[4];
	
	if(rank == 2){
		a[0]=10; 
		a[1]=20; 
		a[2]=30; 
		a[3]=40;
	}
    
    MPI_Scatter(a, 1, MPI_INT, &b, 1, MPI_INT, 2, MPI_COMM_WORLD);

    printf("Process %d: %d \n",  rank, b);

    MPI_Finalize();
    return 0;
}