#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int numArray[64];
    int localArray[16];
    int i;

    if (rank == 0) {
        FILE *input;
        input = fopen("./number.txt", "r");

        for (i = 0; i<64; i++) {
            fscanf(input, "%d", &numArray[i]);
        }
        MPI_Scatter(&numArray, 64, MPI_INT, )
    }

    MPI_Scatter(&numArray, 16, MPI_INT, &localArray, 16, MPI_INT, 0, MPI_COMM_WORLD);
    int localSum;

    for (i = 0; i < 16; i++) {
      localSum += localArray[i];
    }
    printf("Process %d has local sum: %d\n", rank, localSum);

    int localSumArray[4];
    MPI_Gather(&localSum, 1, MPI_INT, &localSumArray, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
      int globalSum = 0;
      for (i = 0; i < 4; i++) {
        globalSum += localSumArray[i];
      }
      printf("Process %d has global sum:: %d\n", rank, globalSum);
    }

    MPI_Finalize();
    return 0;
}