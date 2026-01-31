      module signal_batch
          integer :: batch_terminate_signal = 0
      end module signal_batch
!=======================================================================
      program testapp

      use signal_batch, only : batch_terminate_signal
      use mpi

      implicit none


      ! arguments
      character(len=255) :: cmd
      integer :: itstart = 1

      ! local variables
      intrinsic signal, sleep
      external batch_timeout

      character cdate*8,ctime*10
      character :: end*20,fname*120,form*4
      integer :: it, mpi_rank, ierror, do_timeout, stat, num_args

      ! initialize communicator
      call MPI_Init(ierror)
      call MPI_Comm_rank(MPI_COMM_WORLD,mpi_rank,ierror)

      num_args = command_argument_count()
      if (num_args .ge. 1) then
         call get_command_argument(1,cmd)
         read(cmd,*,iostat=stat)  itstart
      endif

      if (mpi_rank .eq. 0) call signal(23, batch_timeout) ! SIGSTOP

      do it=itstart,10000 ! main iteration loop

        call sleep(1)

        do_timeout = batch_terminate_signal
        call MPI_BCAST(do_timeout, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, ierror)

        if(do_timeout .eq. 1) then
          if(mpi_rank.eq.0) then
            call date_and_time(date=cdate, time=ctime)
            write (*,'(i6," RESTART: ",a6," on ",a8)') it,ctime,cdate
            open(unit=97,file="RESTART",status='unknown')
            write(97,'(i6," RESTART: ",a6," on ",a8)') it,ctime,cdate
            close(97)

            fname="checkpoint"//'.'//"xxxxx"
            open(unit=96,file=fname)
            write(96,'(i6," Restart Checkpoint ",a6," on ",a8)') it,ctime,cdate
            close(96)
         endif
         call MPI_Finalize(ierror)
         stop
        endif

        if(mod(it,60) .eq. 0 ) then
          if(mpi_rank.eq.0) then
            write(form,'(a2,I1,a1)')"(I", &
                        int(log10(dble(it)))+1,")"
            write(end,form)it

            write(form,'(a2,I1,a1)')"(I", &
                        int(log10(dble(it)))+1,")"
            write(end,form)it

            fname="checkpoint"//'.'//end
            call date_and_time(date=cdate, time=ctime)
            write (*,'(i6,1x,"Checkpoint: ",a6," on ",a8)') it,ctime,cdate
            open(unit=99,file=fname)
            write (99,'(i6,1x,"Checkpoint: ",a6," on ",a8)') it,ctime,cdate
            close(99)
          endif
        endif

      enddo ! main iteration loop

      if(mpi_rank.eq.0) then
        call date_and_time(date=cdate, time=ctime)
        write (*,'("DONE: ",a6," on ",a8)') ctime,cdate
        open(unit=97,file="DONE",status='unknown')
        write(97,'(i8)') it
        write (97,'("DONE: ",a6," on ",a8)') ctime,cdate
        close(97)
      endif

      stop
      end program testapp

!=======================================================================

      subroutine batch_timeout
      use signal_batch, only : batch_terminate_signal

      implicit none

      character cdate*8,ctime*10

      call date_and_time(date=cdate, time=ctime)
      write(*,'("Batch timeout at ",a6," on ",a8)') ctime, cdate
      batch_terminate_signal = 1

      return
      end subroutine batch_timeout
