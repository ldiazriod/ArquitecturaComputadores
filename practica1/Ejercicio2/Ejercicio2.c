#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int userValue;
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Add a number: ");
        scanf("%d", &userValue);
        printf("Al proceso %d le ha entrado el valor %d y lo va a mandar al proceso %d \n", rank, userValue, rank+1);
        MPI_Send(&userValue, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&userValue, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank+1 < size){
            MPI_Send(&userValue, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
        printf("El proceso %d ha recibido el valor %d del proceso %d \n", rank, userValue, rank-1);
    }
    MPI_Finalize();
    return 0;
}