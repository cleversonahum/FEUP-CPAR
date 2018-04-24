#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <mpi.h>
#include <math.h>

using namespace std;

void se(int n, string filename) {
	ofstream file; //CSV file

	std::vector<bool> primes(n+1, true);

	file.open(filename);
	file << "Primes until " << n << "\n";

	for (int p=2; (p*p)<=n; p++) {
		if (primes[p] == true) {
			for (int i=p*2; i<=n; i += p)
				primes[i] = false;
		}
	}

	for (int p=2; p<=n; p++)
		if (primes[p])
			file << p << " ";

	file.close();
}

void se(int n, string filename, int nt) {
	ofstream file; //CSV file
	int sn = sqrt(n);
	std::vector<bool> primes(n+1, true);

	file.open(filename);
	file << "Primes until " << n << "\n";

#pragma omp parallel for num_threads(nt)
	for (int p=2; p<=sn; p++) {
		if (primes[p] == true) {
			for (int i=p*2; i<=n; i += p)
				primes[i] = false;
		}
	}

	for (int p=2; p<=n; p++)
		if (primes[p])
			file << p << " ";

	file.close();
}

void seP(int n, string filename, int argc, char* argv[]) {
	int rank, size;
	ofstream file; //CSV file
	int sn = sqrt(n);
	std::vector<int> primes(n+1, 1);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int ri= ceil(((float)sn-2.0)/(float)size);
	int limit;

	if(rank==0) {
		cout<<"\nsn: "<<sn<<" size:"<<size;
		cout<<"\nri: "<<ri<<"\n";
	}

	//file.open(filename);

	//if(rank==0)
	//	file << "Primes until " << n << "\n";

	//Calculating multiples and marking array of primes, each processe will have a list of it multiples, so they are not prime numbers already, but they are numbers that are not multiples of the "looped" numbers
	if(rank!=(size-1))
		limit = ((2+rank*ri)+ri-1);
	else
		limit = sn;

	cout<<"\nRank1, p= "<<(2+rank*ri)<<" until "<<limit<<"\n";
	for (int p=(2+rank*ri); p<=limit; p++) {
		cout<<"\nLoop "<<p<<"\n";
		if (primes[p] == 1) {
			for (int i=p*2; i<=n; i += p)
				primes[i] = 0;
		}
	}

	//Printing Primes Numbers
	//cout<<"\nPrimes: \n";
	//for (int i=2; i<=n; i++)
	//	if(primes[i])
	//		cout<<i<<" = "<<primes[i]<<endl;

	MPI_Barrier(MPI_COMM_WORLD); //All process waits here until other process arrives in this barrier

	//Receiving values calculated
	if(rank==0) { //Process 1 is responsible for receive all processed matrixes. Receiving other matrixes of no multiples calculated in all process
		for(int i=0; i<size; i++)
			cout<<"teste";
			//MPI_Recv(&teste, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	//for (int p=2; p<=n; p++)
	//	if (primes[p])
	//		file << p << " ";

	//file.close();

	MPI_Finalize();
}



int main(int argc, char* argv[]) {
	int n = atoi(argv[1]);
	string filename = argv[2];
	//int nt = atoi(argv[3]);
	seP(atoi(argv[1]), argv[2], argc, argv);
	return 0;
}
