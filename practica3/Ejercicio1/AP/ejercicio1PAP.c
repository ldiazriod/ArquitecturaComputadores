#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int size;
    int msg;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Add a number: ");
        scanf("%d", &msg);
        printf("Proceeding to make the squared of your number... \n");
        msg = msg * msg;
        printf("Sending final number %d to all processes... \n", msg);
        for(int i=1; i < size; i++){
            MPI_Send(&msg, 1, MPI_INT, i, 100, MPI_COMM_WORLD);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }else{
        int auxBufMsg;
        int numBufElemRev;
        MPI_Recv(&auxBufMsg, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        if(MPI_Get_count(&status, MPI_INT, &numBufElemRev) == MPI_SUCCESS){
            printf("Rank: %d \n Has recived value %d from rank %d \n", rank, auxBufMsg, status.MPI_SOURCE);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

