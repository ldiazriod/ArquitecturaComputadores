#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int bufSource[9];
    int auxData[3];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        for(int i=0; i < 9; i++){
            bufSource[i] = i;
        }
    }

    MPI_Scatter(&bufSource, 3, MPI_INT, &auxData, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i=0; i < 3; i++){
        auxData[i] = auxData[i] + rank;
    }
    MPI_Gather(&auxData, 3, MPI_INT, &bufSource, 3, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("Result: \n");
        for(int i=0; i < 9; i++){
            if(i+1 != 9){
                printf("%d-", bufSource[i]);
            }else{
                printf("%d", bufSource[i]);
            }
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}