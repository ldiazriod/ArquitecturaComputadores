#include "mpi.h"
#include <stdio.h>


/*
 ______________________________________
|                                      |
| Ejercicio 1: Comunicación Colectiva  |
|______________________________________|

*/

/*
    Planteamiento: 

    Este ejercicio es incluso más fácil que el anterior. Vamos a utilizar MPI_Bcast, que manda el mensaje desde el proceso padre (proceso 0 en este caso)
    al resto de procesos.

    La parte más compleja de este ejercicio es entender que cuando utilizamos MPI_Bcast, el mensaje que reciben los procesos se reciben mediante la propia
    función de MPI_Bcast, por lo que todos los procesos deben ejecutar esta función. De esta manera nos quitamos el if-else y nos quedamos, en el caso de
    que queramos que el mensaje lo añada el usuario por pantalla o queramos modificar el mensaje en algún proceso en especifico, únicamente con el if.

*/



int main(int argc, char** argv){
    int rank;
    int msg;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Add a number: ");
        scanf("%d", &msg);
        printf("Proceeding to make the squared of your number... \n");
        msg = msg * msg;
        printf("Sending final number %d to all processes... \n", msg);
    }

    MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Rank %d has recived value %d \n", rank, msg);

    MPI_Finalize();
    return 0;
}