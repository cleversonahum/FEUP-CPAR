/*
 * aula1.cpp
 *
 *  Created on: 20/02/2018
 *      Author: up201710783
 */

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#define DEBUG 0 

//Protypes
int multMatrix(int d);

int multMatrixP(int d, int np);

int main(int argc, char* argv[]) {

	if (argc > 3) {
		cout << "Invalid number of arguments";
		return -1;
	}

	//multMatrix(atoi(argv[1]));	
	multMatrixP(atoi(argv[1]), atoi(argv[2]));	

	return 0;
}

int multMatrix(int d) {
        
        vector<int> m1(d*d), m2(d*d), mult(d*d);

        //Filling m1 and m2
        for(int i =0; i<d*d; i++) {
                m1[i] = i;
                m2[i] = d*d-i;
        }


        //Filling mult
        for (int i = 0; i<d*d; i++)
                mult[i] = 0;



        // Multiplying matrix 1 and 2
        for(int i = 0; i < d; ++i)
                for(int j = 0; j < d; ++j)
                        for( int k = 0; k < d; ++k)
                        {
                                mult[i*d+j] += m1[i*d+k] * m2[k*d+j];
                        }

        #if DEBUG==1
        //Showing m1 and m2
        for(int i = 0; i<d*d;i++)
                cout<<"valor m1= "<<m1[i]<<"; valor m2= "<<m2[i]<<"\n";

        //Showing mult
        for(int i = 0; i<d*d;i++)
                cout<<"valor = "<<mult[i]<<"\n";
        #endif

        return 0;
}

int multMatrixP(int d, int nt) {

        vector<int> m1(d*d), m2(d*d), mult(d*d);
	int i,j;

        //Filling m1 and m2
        for(int i =0; i<d*d; i++) {
                m1[i] = i;
                m2[i] = d*d-i;
        }


        //Filling mult
        for (int i = 0; i<d*d; i++)
                mult[i] = 0;


	
        // Multiplying matrix 1 and 2
	#pragma omp parallel for private (i,j) num_threads (nt)
        for(int i = 0; i < d; ++i)
                for(int j = 0; j < d; ++j)
                        for( int k = 0; k < d; ++k)
                        {
                                mult[i*d+j] += m1[i*d+k] * m2[k*d+j];
                        }

        #if DEBUG==1
        //Showing m1 and m2
        for(int i = 0; i<d*d;i++)
                cout<<"valor m1= "<<m1[i]<<"; valor m2= "<<m2[i]<<"\n";

        //Showing mult
        for(int i = 0; i<d*d;i++)
                cout<<"valor = "<<mult[i]<<"\n";
        #endif

        return 0;
}
