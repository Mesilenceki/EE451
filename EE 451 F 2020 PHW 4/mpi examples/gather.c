#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int a;
    int b[4] = {0, 0, 0 , 0};
    if(rank  == 0){
        a=10;
    }
    else if( rank  == 1){
  		a=15;
    }
	else if( rank  == 2){
 		a=20;
    }
    else if( rank  == 3){
		a=30;
    }
   MPI_Gather(&a, 1, MPI_INT, b, 1, MPI_INT, 3, MPI_COMM_WORLD);

   printf("Process: %d: b[0] = %d,  b[1] = %d, b[2] = %d, b[4] = %d \n",  rank, b[0], b[1], b[2], b[3]);

    MPI_Finalize();
    return 0;
}