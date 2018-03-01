/*
 * aula1.cpp
 *
 *  Created on: 20/02/2018
 *      Author: up201710783
 */

#include <iostream>
#include <vector>
#include "papi.h"

using namespace std;

#define DEBUG 0 

//Protypes
int multMatrix(int d);
int mult2Matrix(int d);
int multMatrixP(int d, int np);
int mult2MatrixP(int d, int np);

int main(int argc, char* argv[]) {

	if (argc > 4) {
		cout << "Invalid number of arguments";
		return -1;
	}

	//PAPI variables
	float real_time, proc_time,ipc;
	long long ins;
	float real_time_i, proc_time_i, ipc_i;
	long long ins_i;
	int retval;

	if((retval=PAPI_ipc(&real_time_i,&proc_time_i,&ins_i,&ipc_i)) < PAPI_OK)
	{ 
		printf("Could not initialise PAPI_ipc \n");
		printf("retval: %d\n", retval);
		exit(1);
	}

	switch (atoi(argv[1])) {
		case 1:
			multMatrix(atoi(argv[2]));
			break;
		case 2:
			mult2Matrix(atoi(argv[2]));
			break;
		case 3:
			multMatrixP(atoi(argv[2]), atoi(argv[3]));
			break;
		case 4:
			mult2MatrixP(atoi(argv[2]), atoi(argv[3]));
			break;
	}

	if((retval=PAPI_ipc( &real_time, &proc_time, &ins, &ipc))<PAPI_OK)
	{    
		printf("retval: %d\n", retval);
		exit(1);
	}


	printf("Real_time: %f Proc_time: %f Total instructions: %lld IPC: %f\n", 
			real_time, proc_time,ins,ipc);

	/* clean up */
	PAPI_shutdown();

	return 0;
}

int multMatrix(int d) {

	vector<int> m1(d*d), m2(d*d), mult(d*d);

	//Filling m1 and m2
	for(int i =0; i<d*d; i++) {
		m1[i] = i+1;
		m2[i] = d*d-i;
	}


	//Filling mult
	for (int i = 0; i<d*d; i++)
		mult[i] = 0;



	// Multiplying matrix 1 and 2
	for(int i = 0; i < d; ++i)
		for(int j = 0; j < d; ++j){
			for( int k = 0; k < d; ++k)
			{
				mult[i*d+j] += m1[i*d+k] * m2[k*d+j];
			}
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

int mult2Matrix(int d) {

	vector<int> m1(d*d), m2(d*d), mult(d*d);

	//Filling m1 and m2
	for(int i =0; i<d*d; i++) {
		m1[i] = i+1;
		m2[i] = d*d-i;
	}


	//Filling mult
	for (int i = 0; i<d*d; i++)
		mult[i] = 0;



	// Multiplying matrix 1 and 2
	for(int i = 0; i < d; ++i)
		for(int k = 0; k < d; ++k)
			for( int j = 0; j < d; ++j)
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
		m1[i] = i+1;
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



int mult2MatrixP(int d, int nt) {

	vector<int> m1(d*d), m2(d*d), mult(d*d);
	int i,j;

	//Filling m1 and m2
	for(int i =0; i<d*d; i++) {
		m1[i] = i+1;
		m2[i] = d*d-i;
	}


	//Filling mult
	for (int i = 0; i<d*d; i++)
		mult[i] = 0;



	// Multiplying matrix 1 and 2
#pragma omp parallel for private (i,j) num_threads (nt)
	for(int i = 0; i < d; ++i)
		for(int k = 0; k < d; ++k)
			for( int j = 0; j < d; ++j)
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
