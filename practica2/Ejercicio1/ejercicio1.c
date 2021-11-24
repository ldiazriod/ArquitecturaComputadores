#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    int rank;
    char msg[20];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    strcpy(msg, "Hello World!");
    for(int i=0; i < 3; i++){
        if(rank == 0){
            MPI_Send(&msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
            printf("Sending to child message: %s \n", msg);
            MPI_Recv(&msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD, &status);
        }else{
            MPI_Recv(&msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
            printf("Sending to master message: %s \n", msg);
            MPI_Send(&msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}

