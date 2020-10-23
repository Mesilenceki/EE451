#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int a[2];
    int b[2];
    if(rank  == 0){
        a[0] = 2;
        a[1] = 21;
    }
    else if( rank  == 1){
        a[0] = 3;
        a[1] = 4;
    }
	  else if( rank  == 2){
        a[0] = 1;
        a[1] = 7;
    }
    else if( rank  == 3){
        a[0] = 3;
        a[1] = 8;
    }
    MPI_Reduce(a,b,2,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
        printf("b[0] = %d \n",b[0]);
        printf("b[1] = %d \n",b[1]);
    }

    MPI_Finalize();

    return 0;
}