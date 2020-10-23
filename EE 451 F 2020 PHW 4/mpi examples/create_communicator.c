#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


main(int argc, char *argv[])
{
		int size, rank;
		int new_size, new_rank;
		int red=0;
		int green=1;
		
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		printf("COMM_WORLD: From process %d out of %d\n",rank, size);
		
		MPI_Comm newcomm;
		if(rank == 0){
		 	MPI_Comm_split(MPI_COMM_WORLD, red, 0, &newcomm);
		 	MPI_Comm_size(newcomm, &new_size);
			MPI_Comm_rank(newcomm, &new_rank);
		}	
		else if(rank == 1){
			MPI_Comm_split(MPI_COMM_WORLD, red, 1, &newcomm);
		 	MPI_Comm_size(newcomm, &new_size);
			MPI_Comm_rank(newcomm, &new_rank);
		}	
		else if(rank == 2){	
			MPI_Comm_split(MPI_COMM_WORLD, green, 0, &newcomm);
		 	MPI_Comm_size(newcomm, &new_size);
			MPI_Comm_rank(newcomm, &new_rank);
		}
		else if(rank == 3){
			MPI_Comm_split(MPI_COMM_WORLD, green, 1, &newcomm);
		 	MPI_Comm_size(newcomm, &new_size);
			MPI_Comm_rank(newcomm, &new_rank);
		}	
		printf("NEW_COMM: From process %d out of %d,  COMM_WORLD: From process %d out of %d\n",new_rank, new_size, rank, size);
		MPI_Finalize();
}
