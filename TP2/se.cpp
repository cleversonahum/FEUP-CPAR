#include <bits/stdc++.h>
#include <vector>
#include <fstream>

using namespace std;
 
void se(int n, string filename) {
	ofstream file; //CSV file

	std::vector<bool> primes(n+1, true);

	file.open(filename);
	file << "Primes until " << n << "\n";

	for (int p=2; (p*p)<=n; p++) {
		if (primes[p] == true) {
        		for (int i=p*2; i<=n; i += p)
			primes[i] = false;
        	}
	}
 
	for (int p=2; p<=n; p++)
		if (primes[p])
			file << p << "\n";

	file.close();
}

void se(int n, string filename, int nt) {
	ofstream file; //CSV file
	int sn = sqrt(n);
	std::vector<bool> primes(n+1, true);

	file.open(filename);
	file << "Primes until " << n << "\n";

#pragma omp parallel for num_threads(nt)
	for (int p=2; p<=sn; p++) {
		if (primes[p] == true) {
        		for (int i=p*2; i<=n; i += p)
			primes[i] = false;
        	}
	}
 
	for (int p=2; p<=n; p++)
		if (primes[p])
			file << p << "\n";

	file.close();
}
 
int main(int argc, char* argv[]) {
	se(atoi(argv[1]), argv[2]);
	return 0;
}
