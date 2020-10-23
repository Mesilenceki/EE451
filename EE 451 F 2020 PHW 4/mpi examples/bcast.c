#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    char a[10];    
    
    if(rank == 0){
			 strcpy (a,"hello");
    }
    MPI_Bcast(a, 10, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    printf("a of Process %d: %s \n",  rank, a);

    MPI_Finalize();
    return 0;
}



