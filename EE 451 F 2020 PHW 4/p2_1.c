#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[] {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    FILE *input;
    input = fopen("./number.txt", "r");

    int numArray[64];
    int i;

    for (i = 0; i<64; i++) {
        fscanf(input, "%d", &numArray[i]);
    }

    int localSum;

    if (rank == 0) {
        for (i = 0; i<16; i++) {
            localSum += numArray[i];
        }
    } else if (rank == 1) {
        for (i = 16; i<33; i++) {
            localSum += numArray[i];
        }
    } else if (rank == 2) {
        for (i = 33; i<48; i++) {
            localSum += numArray[i];
        }
    } else if (rank == 3) {
        for (i = 47; i<63; i++) {
            localSum += numArray[i];
        }
    }

    int globalSum;
    MPI_Reduce(&localSum, &globalSum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Process %d got total sum: %d\n", rank, globalSum);
    }

    MPI_Finalize();
    return 0;
})
