/*
 * aula1.cpp
 *
 *  Created on: 20/02/2018
 *      Author: up201710783
 */

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

int main() {
	int r1, c1, r2, c2;

	//Initializing Seed to random number
	srand (time(0));

	cout << "Enter quantity of rows and columns for first matrix: ";
	cin >> r1 >> c1;

	cout << "Enter quantity of rows and columns for second matrix: ";
	cin >> r2 >> c2;

	if (c1!=r1) {
		cout << "Columns of the first matrix need to be equal the second matrix";
		return -1;
	}

	int m1[r1][c1], m2[r2][c2], mult[c1][r2];

	//Filling m1 and m2
	for (int i = 0; i<r1; i++) {
		for (int j = 0; j<c1; j++) {
			m1[i][j] = rand() % 10 + 1;
			m2[i][j] = rand() % 10 + 1;
		}
	}

    //Filling mult
    for (int i = 0; i<c1; i++) {
		for (int j = 0; j<r2; j++) {
			mult[i][j] = 0;
		}
	}

   /* //Showing matrix
    for (int i = 0; i<r1; i++) {
		for (int j = 0; j<c1; j++) {
		    cout << m1[i][j];
		}
	}*/

	// Multiplying matrix 1 and 2
	for(int i = 0; i < r1; ++i)
		for(int j = 0; j < c2; ++j)
			for( int k = 0; k < c1; ++k)
	        {
				mult[i][j] += m1[i][k] * m2[k][j];
	        }

	//Showing matrix
	for (int i = 0; i<c1; i++) {
		for (int j = 0; j<r2; j++) {
			cout << mult[i][j]<<"teste";
		}
	}

	return 0;
}
