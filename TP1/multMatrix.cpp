/*
 * aula1.cpp
 *
 *  Created on: 20/02/2018
 *      Author: up201710783
 */

#include <iostream>
#include <vector>
#include "papi.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;


//Protypes
int multMatrix(int d);
int mult2Matrix(int d);
int multMatrixP(int d, int np);
int mult2MatrixP(int d, int np);
void handle_error(int err);

int main(int argc, char* argv[]) {

	if (argc > 4) {
		cout << "Invalid number of arguments";
		return -1;
	}

	//PAPI Variables
#ifdef IPC
	//IPC variables
	float real_time, proc_time,ipc;
	long long ins;
	float real_time_i, proc_time_i, ipc_i;
	long long ins_i;
	int retval;
#endif

#ifdef CACHE
	//CACHE variables
	int numEvents = 2;
	long long values[2];
	//int events[6] = {PAPI_L1_DCA, PAPI_L1_DCH, PAPI_L1_DCM, PAPI_L2_DCA, PAPI_L2_DCH, PAPI_L2_DCM};
	int events[2] = {PAPI_L2_DCA, PAPI_L2_DCM};
#endif
	//END PAPI Variables

	
#ifdef IPC
	//Starting PAPI IPC
	if((retval=PAPI_ipc(&real_time_i,&proc_time_i,&ins_i,&ipc_i)) < PAPI_OK)
	{ 
		printf("Could not initialise PAPI_ipc \n");
		printf("retval: %d\n", retval);
		exit(1);
	}
#endif


#ifdef CACHE
	//Starting PAPI CACHE
	if (PAPI_start_counters(events, numEvents) != PAPI_OK)
		handle_error(1);
#endif

	//Choosing function
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


#ifdef IPC
	//Finishing PAPI IPC
	if((retval=PAPI_ipc( &real_time, &proc_time, &ins, &ipc))<PAPI_OK)
	{    
		printf("retval: %d\n", retval);
		exit(1);
	}

	//printf("Real Time\tProc Time\tTotal Instructions\tIPC");
	printf("%f\t%f\t%lld\t%f\n", 
			real_time, proc_time,ins,ipc);
	PAPI_shutdown();
#endif 

#ifdef CACHE
	if ( PAPI_stop_counters(values, numEvents) != PAPI_OK)
		handle_error(1);
	
	//printf("L1 DCA\tL1 DCH\tL1 DCM\tL2 DCA\tL2 DCH\tL2 DCM");
	//printf("%lld\t%lld\t%lld\t%lld\t%lld\t%lld\n",
			//values[0],values[1],values[2],values[3],values[4],values[5]);
	printf("%lld\t%lld\n",
			values[0],values[1]);
#endif

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

	return 0;
}


void handle_error(int err){
	std::cerr << "PAPI error: " << err << std::endl;
}
