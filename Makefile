CC=g++
CFLAGS=-fopenmp -lpapi -O3

cache: multMatrix.cpp
	$(CC) -o multMatrixCache multMatrix.cpp -DCACHE $(CFLAGS) 
ipc: multMatrix.cpp
	$(CC) -o multMatrixIPC multMatrix.cpp -DIPC $(CFLAGS) 

all: cache ipc 

clean:
	rm multMatrixCache multMatrixIPC
