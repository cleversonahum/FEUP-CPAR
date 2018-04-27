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

		//Printing Upper
   		float z = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j >= i) 
					printf("% *.*f\t", 4, 2, mat[i * n + j]);
				else 
					printf("% *.*f\t", 4, 2, z);
				
      			}
      			cout<<endl;
   		}

		//Printing Lower
		z = 0;
		int u = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j > i) {
					printf("% *.*f\t", 4, 2, z);
				} else if (i == j) {
					printf("% *.*f\t", 4, 2, u);
				} else {
					printf("% *.*f\t", 4, 2, mat[i * n + j]);
				}
			}
      			cout<<endl;
		}
	}
	
	MPI_Finalize();

}


int readCSV(string csvFile, vector<vector<double>> &mat, int d) { //stores in a bidimentional array

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

int readCSVmpi(string csvFile, vector<float> &mat, int d) { //stores in a unidimentional array

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

	int n = atoi(argv[2]);
	string file = argv[1];
	//int nt = atoi(argv[3]); 
	//vector <vector <double>> mat(n, vector<double>(n));
	vector <float> mat(n*n);
	readCSVmpi(file, mat, n);
	lu(mat, n, argc, argv);

	return 0;
}
