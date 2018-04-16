#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h> 

using namespace std;

void lu(vector<vector<double>> mat, int n)
{

	vector<vector<double> > lower(n, vector<double>(n)), upper(n, vector<double>(n));

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

	// setw is for displaying nicely
	cout << setw(6) << "      Lower Triangular"
		<< setw(32) << "Upper Triangular" << endl;

	// Displaying the result :
	for (int i = 0; i < n; i++) {
		// Lower
		for (int j = 0; j < n; j++)
			cout << setw(6) << lower[i][j] << "\t"; 
		cout << "\t";

		// Upper
		for (int j = 0; j < n; j++)
			cout << setw(6) << upper[i][j] << "\t";
		cout << endl;
	}
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
int main()
{
	vector <vector <double>> mat(3, vector<double>(3));

	readCSV("./matrix.csv", mat, 3);

	return 0;
}
