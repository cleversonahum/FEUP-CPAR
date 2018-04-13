#include <bits/stdc++.h>
#include <vector>
#include <fstream>

using namespace std;
 
void se(int n,string nameCSV) {
	ofstream file; //CSV file

	std::vector<bool> primes(n+1, true);

	file.open(nameCSV);
	file << "Primes until " << n << "\n";

	for (int p=2; p*p<=n; p++) {
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
 
int main() {
	se(10, "primes.csv");
	return 0;
}
