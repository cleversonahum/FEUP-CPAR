#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <mpi.h>
#include <math.h>
#include <time.h>

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

void se(int n, string filename, int argc, char* argv[]) {
	int rank, size;
	ofstream file; //CSV file
	int sn = sqrt(n);
	std::vector<int> primes(n+1, 1);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int ri= ceil(((float)sn-2.0)/(float)size);
	int limit;

	if(rank!=(size-1))
		limit = ((2+rank*ri)+ri-1);
	else
		limit = sn;

	for (int p=(2+rank*ri); p<=limit; p++) {
		if (primes[p] == 1) {
			for (int i=p*2; i<=n; i += p)
				primes[i] = 0;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD); //All process waits here until other process arrives in this barrier
	if(rank!=0) { //Sending primes array to process with rank 0
		MPI_Request status;
		MPI_Isend(primes.data(), primes.size(), MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
	}
	else { //Process 0
		vector<vector<int>> number(size-1, vector<int>(n+1));
		MPI_Request req[size-1];
		MPI_Status status[size-1];

		for(int i = 0; i<(size-1); i++) //Receiving from processes
			MPI_Irecv(&number[i][0], (n+1), MPI_INT, (i+1), (i+1), MPI_COMM_WORLD, &req[i]);

		for(int i = 0; i<(size-1); i++) //Waiting Received values to Number array
			MPI_Wait(&req[i], &status[i]);

		for(int j=0; j<(size-1);j++) //Comparing received values with primes generated
			for(int i=0; i<primes.size();i++)
				primes[i] &= number[j][i];

		file.open(filename);
		file << "Primes until " << n << "\n";
		if(rank==0)
			for (int p=0; p<primes.size(); p++)
				if (primes[p])
					file << p << " ";
		file.close();
	}


	MPI_Finalize();
}



int main(int argc, char* argv[]) {

	if (argc > 5) {
		cout << "Invalid number of arguments";
		return -1;
	}

	int n = atoi(argv[3]);
	string filename = argv[2];
	int nt = atoi(argv[4]);

	clock_t tStart = clock();

	switch (atoi(argv[1])) {
		case 1: //Sequential
			se(n, filename);
			break;
		case 2: //OpenMP
			se(n,filename,nt);
			break;
		case 3: //OpenMPI
			se(n, filename, argc, argv);
			break;
		default:
			cout<<"Command Not Found";
			break;
        }

	cout<<n<<"\t"<<((double)(clock() - tStart)/CLOCKS_PER_SEC);
	
	return 0;
}
