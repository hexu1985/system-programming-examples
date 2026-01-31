#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mpi.h>

static int batch_terminate_signal = 0;
void batch_timeout(int signum){
   printf("Batch Timeout : %d\n",signum);
   batch_terminate_signal = 1;
   return;
}

int main(int argc, char *argv[])
{
   MPI_Init(&argc, &argv);
   char checkpoint_name[50];
   int mype, it, itstart = 1;
   MPI_Comm_rank(MPI_COMM_WORLD, &mype);

   if (argc >=2) itstart = atoi(argv[1]);
   // if (istart > 0) read_restart;

   if (mype ==0) signal(23, batch_timeout);

   for (it=itstart; it < 10000; it++){
      sleep(1);

      if ( it%60 == 0 ) {
         if (mype == 0){
            time_t tval = time(NULL);
            printf("%d %s: %s", it, "Checkpoint", ctime(&tval));
            sprintf(checkpoint_name,"checkpoint.%05d",it);
            FILE *fp = fopen(checkpoint_name, "w+");
            fprintf(fp,"%d %s: %s", it, "Checkpoint", ctime(&tval));
            fclose(fp);
         }
      }
      int terminate_sig = batch_terminate_signal;
      MPI_Bcast(&terminate_sig, 1, MPI_INT, 0, MPI_COMM_WORLD);
      if ( terminate_sig ) {
         if (mype == 0){
            time_t tval = time(NULL);
            printf("%d %s: %s", it, "RESTART", ctime(&tval));
            FILE *fp = fopen("RESTART", "w+");
            fprintf(fp,"%d %s: %s", it, "RESTART", ctime(&tval));
            fclose(fp);
            fp = fopen("checkpoint.xxxxx", "w+");
            fprintf(fp,"%d %s: %s", it, "Restart Checkpoint", ctime(&tval));
            fclose(fp);
         }
         MPI_Finalize();
         exit(0);
      }

   }

   if (mype == 0){
      time_t tval = time(NULL);
      printf("%s: %s", "DONE", ctime(&tval));
      FILE *fp = fopen("DONE", "w+");
      fprintf(fp,"%s: %s", "DONE", ctime(&tval));
      fclose(fp);
   }
   MPI_Finalize();
   return(0);
}
