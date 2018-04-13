#include <bits/stdc++.h>
#include <vector>

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

int main()
{
	vector <vector <double>> mat(3, vector<double>(3));

	mat[0][0] = 2;
	mat[0][1] = -1;
	mat[0][2] = -2;
	mat[1][0] = -4;
	mat[1][1] = 6;
	mat[1][2] = 3;
	mat[2][0] = -4;
	mat[2][1] = -2;
	mat[2][2] = 8;

	//int mat[][100] = { { 2, -1, -2 },
	//{ -4, 6, 3 },
	//{ -4, -2, 8 } };

	lu(mat, 3);
	return 0;
}
