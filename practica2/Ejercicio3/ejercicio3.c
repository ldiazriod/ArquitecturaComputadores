#include <mpi.h>
#include <stdio.h>

float * initArray(float rank){
    float static aux[1000];
    for(int i=0; i < 1000; i++){
        aux[i] = rank;
    }
    return aux;
}

int main(int argc, char** argv){
    int rank;
    int size;
    int numSElements;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        float *A = initArray(rank);
        float B[1000];
        MPI_Send(A, 1000, MPI_FLOAT, rank+1, 100, MPI_COMM_WORLD);
        MPI_Recv(B, 1000, MPI_FLOAT, size-1, 100, MPI_COMM_WORLD, &status);
        if(MPI_Get_count(&status, MPI_FLOAT, &numSElements) == MPI_SUCCESS){
            printf("Rank: %d. \n Recived %d elements from process %d. \n Value recived: %lf \n", rank, numSElements, status.MPI_SOURCE, B[100]);
        }
    }else{
        float *A = initArray(rank);
        float B[1000];
        MPI_Recv(B, 1000, MPI_FLOAT, rank-1, 100, MPI_COMM_WORLD, &status);
        if(MPI_Get_count(&status, MPI_FLOAT, &numSElements) == MPI_SUCCESS){
            printf("Rank: %d. \n Recived %d elements from process %d. \n Value recived: %lf \n", rank, numSElements, status.MPI_SOURCE, B[100]);
        }
        if(rank != size-1){
            MPI_Send(A, 1000, MPI_FLOAT, rank+1, 100, MPI_COMM_WORLD);
        }else{
            MPI_Send(A, 1000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}


