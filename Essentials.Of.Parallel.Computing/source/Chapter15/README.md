# Chapter 15 Batch schedulers: bringing order to chaos
This is from Chapter 15 of Parallel and High Performance Computing, Robey and Zamora
Manning Publications, available at http://manning.com

The book may be obtained at
   http://www.manning.com/?a_aid=ParallelComputingRobey

Copyright 2019-2020 Robert Robey, Yuliana Zamora, and Manning Publications
Emails: brobey@earthlink.net, yzamora215@gmail.com

See License.txt for licensing information.

Using batch schedulers
   Requirements: a batch system to work on

Slurm batch script (Book: listing 15.1)
   cd Slurm_first_batch
   Build with cmake
      mkdir build && cd build
      cmake .. && make
   Submit with sbatch < first_slurm_batch_job

PBS batch script (Book: listing 15.2)
   cd PBS_first_batch
   Build with cmake
      mkdir build && cd build
      cmake .. && make
   Submit with qsub < first_pbs_batch_job

Automatic restarts (Book: listing 15.3 - 15.4)
   cd AutomaticRestarts
   make
   sbatch batch_restart.sh

Fortran restarts
   cd Fortran_Restarts
   make
   sbatch batch_restart.sh

Prestart (Book: listing 15.5) 
   cd Prestart
   make
   sbatch batch_restart.sh

clean:
   cd Slurm_first_batch && rm -rf build
   cd AutomaticRestarts && make clean
   cd Fortran_Restarts && make clean
   cd Prestart && make clean
   
