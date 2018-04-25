#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h> 
#include <mpi.h>
#include <math.h>

using namespace std;

void lu(vector<vector<double>> mat, int n) {

	vector<vector<double> > lower(n, vector<double>(n)), upper(n, vector<double>(n));
	ofstream l, u;


	for (int i = 0; i < n; i++) {
		// Upper
		for (int k = i; k < n; k++) {
			// Sum L(i, j) * U(j, k)
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);

			// U(i, k)
			upper[i][k] = mat[i][k] - sum;
		}


		// Lower 
		for (int k = i; k < n; k++) {
			if (i == k)
				lower[i][i] = 1; // Diagonal
			else {

				// Sum L(k, j) * U(j, i)
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower[k][j] * upper[j][i]);

				// L(k, i)
				lower[k][i] = (mat[k][i] - sum) / upper[i][i];
			}
		}

	}

	//Writing CSV
	u.open("U.csv");
	l.open("L.csv");
	for (int i = 0; i < n; i++) {
		// Lower
		for (int j = 0; j < n; j++)
			l << lower[i][j] << "\t"; 

		// Upper
		for (int j = 0; j < n; j++)
			u << upper[i][j] << "\t";
		u << endl;
		l << endl;
	}

	u.close();
	l.close();
}

void lu(vector<vector<double>> mat, int n, int nt) {

	vector<vector<double> > lower(n, vector<double>(n)), upper(n, vector<double>(n));
	ofstream l, u;

#pragma omp parallel for num_threads(nt)
	for (int i = 0; i < n; i++) {
		// Upper
		for (int k = i; k < n; k++) {
			// Sum L(i, j) * U(j, k)
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);

			// U(i, k)
			upper[i][k] = mat[i][k] - sum;
		}


		// Lower 
		for (int k = i; k < n; k++) {
			if (i == k)
				lower[i][i] = 1; // Diagonal
			else {

				// Sum L(k, j) * U(j, i)
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower[k][j] * upper[j][i]);

				// L(k, i)
				lower[k][i] = (mat[k][i] - sum) / upper[i][i];
			}
		}

	}

	//Writing CSV
	u.open("U.csv");
	l.open("L.csv");
	for (int i = 0; i < n; i++) {
		// Lower
		for (int j = 0; j < n; j++)
			l << lower[i][j] << "\t"; 

		// Upper
		for (int j = 0; j < n; j++)
			u << upper[i][j] << "\t";
		u << endl;
		l << endl;
	}

	u.close();
	l.close();
}

void lu(vector<vector<double>> mat, int n, int argc, char* argv[]) {

	vector<double> lower(n*n), upper(n*n);
	ofstream l, u;
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int limit, ri;
	ri = ceil(((float)n)/(float)size);

	if(rank!=(size-1)) //Defining Limits for Loops
		limit = (rank*ri)+ri;
	else
		limit = n;

	for (int i = (rank*ri); i < limit; i++) { //Calculating upper and lower matrix
		// Upper
		for (int k = i; k < n; k++) {
			// Sum L(i, j) * U(j, k)
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i*n+j] * upper[j*n+k]);

			// U(i, k)
			upper[i*n+k] = mat[i][k] - sum;
		}


		// Lower 
		for (int k = i; k < n; k++) {
			if (i == k)
				lower[i*n+i] = 1; // Diagonal
			else {

				// Sum L(k, j) * U(j, i)
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower[k*n+j] * upper[j*n+i]);

				// L(k, i)
				lower[k*n+i] = (mat[k][i] - sum) / upper[i*n+i];
			}
		}

	}

	MPI_Barrier(MPI_COMM_WORLD);

	if(rank!=0) { //Sending array to process with rank 0
		MPI_Request req[2];
		MPI_Isend(upper.data(), upper.size(), MPI_DOUBLE, 0, rank*rank, MPI_COMM_WORLD, &req[0]);
		MPI_Isend(lower.data(), lower.size(), MPI_DOUBLE, 0, rank*rank+1, MPI_COMM_WORLD, &req[1]);
	}
	else { //Process 0
		vector<vector<double>> received(size-1, vector<double>(n*n));
		MPI_Request req[(size-1)*2];
		MPI_Status status[(size-1)*2];
		int cont = 1;

		for(int i=0; i<(size-1); i++) { //Receiving from process {
			MPI_Irecv(&received[i][0], received.size(), MPI_DOUBLE, i+1, (i+1)*(i+1), MPI_COMM_WORLD, &req[i*cont]);
			MPI_Irecv(&received[i][0], received.size(), MPI_DOUBLE, i+1, (i+1)*(i+1)+1, MPI_COMM_WORLD, &req[i*cont+1]);
			cont++;
		}

		for(int i = 0; i<2*(size-1);i++) //Waiting received values
			MPI_Wait(&req[i], &status[i]);

		//DO MAGIC HERE


		//Writing CSV
		u.open("U.csv");
		l.open("L.csv");
		for (int i = 0; i < n; i++) {
			// Lower
			for (int j = 0; j < n; j++)
				l << lower[i*n+j] << "\t"; 

			// Upper
			for (int j = 0; j < n; j++)
				u << upper[i*n+j] << "\t";
			u << endl;
			l << endl;
		}

		u.close();
		l.close();

	}

	MPI_Finalize();

}


	int readCSV(string csvFile, vector<vector<double>> &mat, int d) {

		std::ifstream file(csvFile);

		string readNumber;
		int line = 0;

		while(file.good()) {

			for(int j=0; j<d; j++) {

				if(j==(d-1))
					getline(file,readNumber);
				else 
					getline(file,readNumber,'\t');

				if(line<=d-1)
					mat[line][j] = stod(readNumber);
			}

			line++;
		}

		file.close();
	}


	int main(int argc, char* argv[])
	{
		int n = atoi(argv[2]);
		string file = argv[1];
		int nt = atoi(argv[3]); 
		vector <vector <double>> mat(n, vector<double>(n));

		readCSV(file, mat, n);

		lu(mat, n, nt);

		return 0;
	}
