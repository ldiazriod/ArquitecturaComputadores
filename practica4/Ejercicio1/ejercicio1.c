#include "mpi.h"
#include <stdio.h>

void printArray(int *arr){
    for(int i=0; i < 4; i++){
        if(i != 3){
            printf("%d,", arr[i]);
        }else{
            printf("%d", arr[i]);
        }
    }
    printf("\n");
}

//TODO: Sacar correctamente por pantalla la matriz final.

int main(int argc, char **argv){
    int rank;
    int matrix[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sendBuffer[4];
    for(int i=0; i < 4; i++){
        sendBuffer[i] = matrix[rank][i];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d data --> ", rank);
    printArray(sendBuffer);
    MPI_Barrier(MPI_COMM_WORLD);
    int recvBuffer[4];
    printf("\n");
    MPI_Alltoall(&sendBuffer, 1, MPI_INT, &recvBuffer, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    printArray(recvBuffer);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

/*

          Data partition                      Data patition
         0    1    2    3       !          0    1    2    3
      |--------------------|    !       |--------------------|
P   0 | 1  |  2 |  3 |  4  |    !     0 | 1  |  5 |  9 |  13 |
r     |--------------------|    !       |--------------------|
o   1 | 5  |  6 |  7 |  8  |    !     1 | 2  |  6 | 10 |  14 |  
c     |--------------------|    !       |--------------------| 
e   2 | 9  | 10 | 11 |  12 |    !     2 | 3  |  7 | 11 |  15 | 
s     |--------------------|    !       |--------------------|
s   3 | 13 | 14 | 15 |  16 |    !     3 | 4  |  8 | 12 |  16 |
      |--------------------|    !       |--------------------| 

    MPI_Alltoall() -- Creo --
*/