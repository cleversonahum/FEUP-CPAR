#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h> 

using namespace std;

void lu(vector<vector<double>> mat, int n)
{

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
	int n = atoi(argv[1]);
	string file = argv[2];
	vector <vector <double>> mat(n, vector<double>(n));

	readCSV(file, mat, n);

	lu(mat, n);

	return 0;
}
