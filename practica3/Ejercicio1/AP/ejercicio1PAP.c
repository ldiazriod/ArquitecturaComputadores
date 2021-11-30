#include "mpi.h"
#include <stdio.h>

/*
 __________________________________________
|                                          |
| Ejercicio 1: Comunicación Punto a punto  |
|__________________________________________|

*/

/*
    Planteamiento: 

    Para este ejercicio la cominicación punto a punto es un poco distinta. No vamos mandando la información de un proceso al otro, si no que la información
    se manda desde un nodo inicial o padre a todos los procesos. 

    Para resolver esto, podemos basarnos parcialmente en el planteamiento del ejercicio 3 de la práctica 2. La principal diferencia es que el proceso 0 es
    el único que manda el mensaje, y el resto de procesos únicamente reciben la información y no la mandan a ninguna parte.

    Esto supone el problema inicial en el que debemos mandar la información a todos los procesos desde el proceso 0. Para ello la mejor solución que se me 
    ha ocurrido es utilizar un bucle "for" con el que mandar a cada proceso correspondiente un mensaje. 

    La función MPI_Send recibiría como parametros el valor inicial modificado, el tamaño, el tipo de dato, el número de iteración (i) y el comm. Para esto,
    el bucle "for" empezaría en i=1 (Para empezara a mandar el mensaje al proceso 1) e iría aumentado hasta llegar al número de procesos-1 (El último proceso).

    El resto de procesos reciben la información y la imprimen.

    Este ejercicio es sencillo

*/

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