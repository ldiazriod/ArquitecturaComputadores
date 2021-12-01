#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int msg;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Add a number: ");
        scanf("%d", &msg);
        printf("Proceeding to make the squared of your number... \n");
        msg = msg * msg;
        printf("Sending final number %d to all processes... \n", msg);
    }

    MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Rank %d has recived value %d \n", rank, msg);

    MPI_Finalize();
    return 0;
}

