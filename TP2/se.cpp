#include <bits/stdc++.h>
#include <vector>
using namespace std;
 
void se(int n) {

	std::vector<bool> primes(n+1, true);

	for (int p=2; p*p<=n; p++) {
		if (primes[p] == true) {
        		for (int i=p*2; i<=n; i += p)
			primes[i] = false;
        	}
	}
 
	for (int p=2; p<=n; p++)
		if (primes[p])
			cout << p << " ";
}
 
int main() {
	se(10000000);
	return 0;
}
