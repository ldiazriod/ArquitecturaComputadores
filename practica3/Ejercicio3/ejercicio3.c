#include "mpi.h"
#include <stdio.h>

void printArray(int * toPrint, int arrSize){
    for(int i=0; i < arrSize; i++){
        if(i+1 != arrSize){
            printf("%d-", toPrint[i]);
        }else{
            printf("%d", toPrint[i]);
        }
    }
    printf("\n");
}

int main(int argc, char** argv){
    int rank;
    int finalBufSum[3];
    int finalBufMul[3];
    int auxData[3];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(int i=0; i < 3; i++){
        auxData[i] = rank + 1;
    }

    MPI_Reduce(&auxData, &finalBufSum, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&auxData, &finalBufMul, 3, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Sum result: ");
        printArray(finalBufSum, 3);
        printf("Product result: ");
        printArray(finalBufMul, 3);
    }

    MPI_Finalize();

    return 0;
}

/*
 arr0 = [1, 1, 1]
 arr1 = [2, 2, 2]
 arr2 = [3, 3, 3]

 1 * 2 * 3 = 6

 arrFinalSum = [6,6,6]


*/