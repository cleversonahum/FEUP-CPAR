#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int randNum(int min, int max);

int main(int argc, char* argv[]) {
	int dim = atoi(argv[2]);
	string filename = argv[1];
	ofstream file;
	srand(time(0));

	file.open(filename);

	for(int i=0; i<dim;i++)
		for(int j=0; j<dim; j++)
			if(j==(dim-1))
				file << randNum(0,10) << "\n";
			else
				file << randNum(0,10) << "\t";
	file.close();

}

int randNum(int min, int max) {
	return rand() % max + min;
}
