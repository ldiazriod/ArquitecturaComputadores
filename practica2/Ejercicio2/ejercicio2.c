#include <mpi.h>
#include <stdio.h>

float * initArray(float rank){
    float static aux[10000];
    for(int i=0; i < 10000; i++){
        aux[i] = rank;
    }
    return aux;
}

int main(int argc, char** argv){
    int rank;
    int counter = 1;
    int aux;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    do{
        if(rank == 0){
            float *A = initArray(rank);
            float B[10000];
            MPI_Send(A, 10000, MPI_FLOAT, 1, 200, MPI_COMM_WORLD);
            counter++;
            MPI_Recv(B, 10000, MPI_FLOAT, 1, 200, MPI_COMM_WORLD, &status);
            if(counter == 3){
                if(MPI_Get_count(&status, MPI_FLOAT, &aux) == MPI_SUCCESS){
                    printf("Sources: %d\n", status.MPI_SOURCE);
                }
                printf("Rank %d has %lf from array B\n\n", rank, B[0]);
            }
        }else{
            float *A = initArray(rank);
            float B[10000];
            MPI_Send(A, 10000, MPI_FLOAT, 0, 200, MPI_COMM_WORLD);
            MPI_Recv(B, 10000, MPI_FLOAT, 0, 200, MPI_COMM_WORLD, &status);
            if(MPI_Get_count(&status, MPI_FLOAT, &aux) == MPI_SUCCESS){
                if(counter == 2){
                    printf("Sources: %d\n", status.MPI_SOURCE);
                    printf("Rank %d has %lf from array B\n\n", rank, B[0]);
                }
                counter++;
            }
        }
    }while(counter != 3);
    MPI_Finalize();
    return 0;
}

/*
Bibliografía:
    MPI_Get_Count: 
        https://www.mpich.org/static/docs/v3.3/www3/MPI_Get_count.html
        https://www.mpich.org/static/docs/v3.3/www3/MPI_Get_count.html
    MPI_SUCCESS:
        https://www.rookiehpc.com/mpi/docs/mpi_success.php
*/