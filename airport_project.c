#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(argc, argv)
int argc;
char *argv[];
{
    int numtasks, rank, dest, source, rc, count, tag = 1;
    char inmsg, outmsg = 'x';
    int damascusTravelers = 300, beirutTravelers = 280, damascusCars = 6, beirutCars = 3, carSize = 4;

    // void print_travelers_left(char);

    MPI_Status Stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    void print_travelers_left(char choice)
    {
        switch (choice)
        {
        case 'd':
        case 'D':
            printf("Travelers Left in Damascus Airport = %d\n", damascusTravelers);
            break;

        case 'b':
        case 'B':
            printf("Travelers Left in Beirut Airport = %d\n", beirutTravelers);
            break;

        default:
            break;
        }
    }

    // Damascus
    if (rank < damascusCars)
    {

        // Are There Available Travelers to Pick-up ?
        if (damascusCars > 0)
        {
            // Can Pick-up 4 People
            if ((damascusTravelers - 4) > 0)
            {
                print_travelers_left('d');
                damascusTravelers -= 4;
                printf("Picked Up (%d) Travelers, My rank= %d\n", carSize, rank);
                print_travelers_left('d');
            }
            else
            {
                print_travelers_left('d');
                printf("Picked Up (%d) Travelers, My rank= %d\n", (carSize - abs(damascusTravelers - carSize)), rank);
                print_travelers_left('d');
            }
        }

        // dest = 1;
        // source = 1;
        // rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag,
        //               MPI_COMM_WORLD);
        // rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag,
        //               MPI_COMM_WORLD, &Stat);
    }

    // Beirut
    else if (rank >= damascusCars)
    {

        // Are There Available Travelers to Pick-up ?
        if (beirutCars > 0)
        {
            // Can Pick-up 4 People
            if ((beirutTravelers - 4) > 0)
            {
                print_travelers_left('b');
                beirutTravelers -= 4;
                printf("Picked Up (%d) Travelers, My rank= %d\n", carSize, rank);
                print_travelers_left('b');
            }
            else
            {
                print_travelers_left('b');
                printf("Picked Up (%d) Travelers, My rank= %d\n", (carSize - abs(beirutTravelers - carSize)), rank);
                print_travelers_left('b');
            }
        }

        // dest = 0;
        // source = 0;
        // rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag,
        //               MPI_COMM_WORLD, &Stat);
        // rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag,
        //               MPI_COMM_WORLD);
    }

    // rc = MPI_Get_count(&Stat, MPI_CHAR, &count);

    // printf("Task %d: Received %d char(s) from task %d with tag %d \n",
    //        rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

    MPI_Finalize();
}