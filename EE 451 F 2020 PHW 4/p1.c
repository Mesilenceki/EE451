#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

main(int argc, char *argv[]) {
    int size, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("COMM_WORLD: From process %d out of %d\n", rank, size);

    int Msg;
    // Receive from the lower process and send to the higher process. Take care
    // of the special case when you are the first process to prevent deadlock.
    if (world_rank != 0) {
        MPI_Recv(&Msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        Msg+=1;
        printf("Process %d: Msg = %d\n", rank, Msg);
    } else {
    // Set the token's value if you are process 0
        Msg = 451;
        prinf("Process %d: Initially Msg = %d\n", rank, Msg)
    }
    MPI_Send(&Msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    // Now process 0 can receive from the last process. This makes sure that at
    // least one MPI_Send is initialized before all MPI_Recvs (again, to prevent
    // deadlock)
    if (world_rank == 0) {
        MPI_Recv(&Msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d: Received Msg = %d. Done!\n", rank, Msg);
    }
    MPI_Finalize();
}