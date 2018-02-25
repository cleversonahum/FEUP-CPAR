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

int main(int argc, char* argv[]) {
	
	if (argc != 3 || atoi(argv[2]) != atoi(argv[1])) {
		cout << "Columns of the first matrix need to be equal the second matrix and number of parameters need to be equal 4";
		return -1;
	}
	
	int r = atoi(argv[1]), c = atoi(argv[2]);
	int m1[r][c], m2[r][c], mult[c][r];

	//Initializing Seed to random number
        srand (time(0));

	//Filling m1 and m2
	for (int i = 0; i<r; i++) {
		for (int j = 0; j<c; j++) {
			m1[i][j] = rand() % 10 + 1;
			m2[i][j] = rand() % 10 + 1;
		}
	}

    //Filling mult
    for (int i = 0; i<c; i++) {
		for (int j = 0; j<r; j++) {
			mult[i][j] = 0;
		}
	}


	// Multiplying matrix 1 and 2
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			for( int k = 0; k < c; ++k)
	        {
				mult[i][j] += m1[i][k] * m2[k][j];
	        }

	//Showing matrix
	//for (int i = 0; i<c1; i++) {:x
	//
	//	for (int j = 0; j<r2; j++) {
	//		cout << mult[i][j]<<"teste";
	//	}
	//}

	return 0;
}
