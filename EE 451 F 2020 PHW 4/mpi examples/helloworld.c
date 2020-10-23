#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


main(int argc, char *argv[])
{
		int npes, myrank;
		
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &npes);  // total number of processes
		MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
		printf("From process %d out of %d, Hello World!\n",myrank, npes);
		
		MPI_Finalize();
}
