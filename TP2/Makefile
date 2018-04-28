MPI=mpic++
FLAGS=-fopenmp -O3

all: se lu 

#SE
se: se.cpp
	$(MPI) -o se se.cpp $(FLAGS)

#LU
lu: lu.cpp
	$(MPI) -o lu lu.cpp $(FLAGS) 
	
clean:
	rm se lu
