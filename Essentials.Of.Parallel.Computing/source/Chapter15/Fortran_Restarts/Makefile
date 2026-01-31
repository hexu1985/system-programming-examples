default: testapp

testapp.o: testapp.F90
	mpifort -g -c testapp.F90

testapp: testapp.o
	mpifort -g testapp.o -o testapp

run: testapp
	sbatch < batch_restart.sh

clean:
	rm -rf testapp testapp.o basic.o *.mod *.out RESTART DONE checkpoint.*
