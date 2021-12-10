#include "mpi.h"
#include <stdio.h>

int main(int argc, char ** argv){
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendBuffer[size];
    for(int i=0; i < size; i++){
        sendBuffer[i] = (1000 * rank) + i + (1 * rank); 
    }

    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d data --> ", rank);
    for(int j=0; j < size; j++){
        printf("%d ", sendBuffer[j]);
    }
    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);

    int recvBuffer[size];
    MPI_Alltoall(&sendBuffer, 1, MPI_INT, &recvBuffer, 1, MPI_INT, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    for(int k=0; k < size; k++){
        printf("%d ", recvBuffer[k]);
    }
    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Finalize();
    return 0;
}