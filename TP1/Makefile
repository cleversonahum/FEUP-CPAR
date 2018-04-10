CC=g++
CFLAGS=-fopenmp -lpapi -O3

all: cache ipc 

cache: multMatrix.cpp
	$(CC) -o multMatrixCache multMatrix.cpp -DCACHE $(CFLAGS) 

ipc: multMatrix.cpp
	$(CC) -o multMatrixIPC multMatrix.cpp -DIPC $(CFLAGS) 

clean:
	rm multMatrixCache multMatrixIPC
