#!/bin/sh
#
# Use this script by submitting with the bsubmit command "sbatch < batch_restart.sh".
#
# Change the environment variables for each problem. The rest of the file should
# not need to be changed. Keep a watch out for runaway behaviors --
# the downside of an automated system.
#
# This script relies heavily on two files, RESTART and DONE, written
# out to the run directory. The application needs to write out a file
# called RESTART if it exits due to a run-time limit.
#
#SBATCH -N 1
#SBATCH -n 4
#SBATCH --signal=23@160
#SBATCH -t 00:08:00

# Do not place bash commands before the last SBATCH directive
# Behavior can be unreliable

NUM_CPUS=${SLURM_NTASKS}
OUTPUT_FILE=run.out
EXEC_NAME=./testapp
MAX_RESTARTS=4

if [ -z ${COUNT} ]; then
   export COUNT=0
fi

((COUNT++))
echo "Restart COUNT is ${COUNT}"

if [ ! -e DONE ]; then
   if [ -e RESTART ]; then
      echo "=== Restarting ${EXEC_NAME} ==="             >> ${OUTPUT_FILE}
      cycle=`cut -f 1 -d " " RESTART`
      rm -f RESTART
   else
      echo "=== Starting problem ==="                    >> ${OUTPUT_FILE}
      cycle=""
   fi

   echo "=== Submitting restart script ==="              >> ${OUTPUT_FILE}
   sbatch --dependency=afterok:${SLURM_JOB_ID} <batch_restart.sh

   mpirun -n ${NUM_CPUS} ${EXEC_NAME} ${cycle}          &>> ${OUTPUT_FILE}
   echo "Finished mpirun"                                >> ${OUTPUT_FILE}

   if [ ${COUNT} -ge ${MAX_RESTARTS} ]; then
      echo "=== Reached maximum number of restarts ==="  >> ${OUTPUT_FILE}
      date > DONE
   fi
fi
