#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
int main(int argc, char *argv[]){
   MPI_Init(&argc, &argv);

   int rank, nprocs;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

   struct timespec tstart, tstop, tresult;
// Start timer, call sleep and stop timer
   clock_gettime(CLOCK_MONOTONIC, &tstart);
   sleep(30);
   clock_gettime(CLOCK_MONOTONIC, &tstop);
// Timer has two values for resolution and prevent overflows
   tresult.tv_sec = tstop.tv_sec - tstart.tv_sec;
   tresult.tv_nsec = tstop.tv_nsec - tstart.tv_nsec;
// Print calculated time from timers
   if (rank == 0) {
      printf("Elapsed time is %f secs\n", (double)tresult.tv_sec +
        (double)tresult.tv_nsec*1.0e-9);
   }
   MPI_Finalize();
}

