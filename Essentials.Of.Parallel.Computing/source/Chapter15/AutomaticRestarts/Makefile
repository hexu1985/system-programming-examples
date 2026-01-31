default: testapp

testapp.o: testapp.c
	mpicc -g -c testapp.c

testapp: testapp.o
	mpicc -g testapp.o -o testapp

run: testapp
	sbatch < batch_restart.sh

clean:
	rm -rf testapp testapp.o *.mod *.out DONE RESTART checkpoint.*
