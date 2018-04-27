#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h> 
#include <mpi.h>
#include <math.h>

using namespace std;

void lu(vector<float> mat, int n) {

	vector<vector<float> > lower(n, vector<float>(n)), upper(n, vector<float>(n));
	ofstream l, u;


	for (int i = 0; i < n; i++) {
		// Upper
		for (int k = i; k < n; k++) {
			// Sum L(i, j) * U(j, k)
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);

			// U(i, k)
			upper[i][k] = mat[i*n+k] - sum;
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
				lower[k][i] = (mat[k*n+i] - sum) / upper[i][i];
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

void lu(vector<float> mat, int n, int nt) {

	vector<vector<float> > lower(n, vector<float>(n)), upper(n, vector<float>(n));
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
			upper[i][k] = mat[i*n+k] - sum;
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
				lower[k][i] = (mat[k*n+i] - sum) / upper[i][i];
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

void lu(vector <float> mat, int n, int argc, char* argv[]) { //Using Forward Gauss Elimination
	int size, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int dref = 0; //diagonal reference

	for (int i = 0; i < n-1; i++, dref++) {
		float *drow = &mat[dref * n + dref]; //Diagonal row
		for (int j = dref + 1; j < n; j++) {
			if (j % size == rank) {
				float *save = &mat[j * n + dref];
				if (*save == 0) //Forward Gauss Elimination
					return;
				float k = *save / drow[0];
				for (int i = 1; i < (n-dref); i++)
					save[i] = save[i] - k * drow[i];
				*save = k;
			}
		}

		for (int j = dref + 1; j < n; j++) {
			float *save = &mat[j * n + dref];
			MPI_Bcast(save, n - dref, MPI_FLOAT, j % size, MPI_COMM_WORLD);
		}
	}

	if(rank==0) {
		ofstream l, u;

		//Writing CSV
        	u.open("U.csv");
		l.open("L.csv");

		//Printing Upper
   		float z = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j >= i)
					u<<mat[i*n+j]<<"\t";
				else 
					u<<z<<"\t";
				
      			}
      			u<<endl;
   		}

		//Printing Lower
		z = 0;
		int k = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j > i) {
					l<<z<<"\t";
				} else if (i == j) {
					l<<k<<"\t";
				} else {
					l<<mat[i*n+j]<<"\t";
				}
			}
      			l<<endl;
		}

		u.close();
		l.close();
	}
	
	MPI_Finalize();

}


int readCSV(string csvFile, vector<float> &mat, int d) { //stores in a unidimentional array

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
				mat[line*d+j] = stod(readNumber);
		}

		line++;
	}

	file.close();
}

int main(int argc, char* argv[]) {
	
	if (argc > 5) {
		cout << "Invalid number of arguments: "<<argc;
		return -1;
	}
	int n= atoi(argv[3]);
	string file = argv[2];
	int nt = atoi(argv[4]);
	vector <float> mat(n*n);

	switch (atoi(argv[1])) {
		case 1: //Sequential
			readCSV(file, mat, n);
			lu(mat, n);
			break;
		case 2: //OpenMP
			readCSV(file, mat, n);
			lu(mat,n,nt);
			break;
		case 3: //OpenMPI
			readCSV(file, mat, n);
			lu(mat, n, argc, argv);
			break;
		default:
			cout<<"Command Not Found";
			break;
	}

	return 0;
}
