MPI=mpic++
FLAGS=-fopenmp -O3

all: se lu matrix buildMatrix

#SE
se: se.cpp
	$(MPI) -o se se.cpp $(FLAGS)

#LU
lu: lu.cpp
	$(MPI) -o lu lu.cpp $(FLAGS) 
#Matrix
matrix: matrixGenerator.cpp
	g++ -o matrixGenerator matrixGenerator.cpp -O3

buildMatrix:
	./matrixGenerator matrix1.csv 1000
	./matrixGenerator matrix2.csv 2000
	./matrixGenerator matrix3.csv 3000
	./matrixGenerator matrix4.csv 4000
	./matrixGenerator matrix5.csv 5000
	./matrixGenerator matrix6.csv 6000


clean:
	rm se lu matrixGenerator matrix{1..6}.csv
