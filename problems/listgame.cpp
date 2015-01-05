#include "general.h"

#define MAX_PRIME 35000 // ~sqr 10^9

void factorize(LL m, vi &primes, vpLLLL &S){
	LL p = primes[0];
	for (LL i = 0; (p*p <= m) && (m != 1) && i < (primes.size()); i++){
		p = primes[i];
		bool pInM = false;
		LL nuoOccurences = 0;
		while (m % p == 0){
			nuoOccurences++;
			m /= p;
			pInM = true;
		}
		if (pInM){
			S.push_back(mp(p, nuoOccurences));
		}
	}
	if (m != 1){
		S.push_back(mp(m, 1));
	}
}

int main() {
	//precalc primes
	vi primes;
	vb isPrime(MAX_PRIME + 1, true);
	isPrime[0] = isPrime[1] = false;
	for (LL i = 2; i*i < MAX_PRIME; i++){
		if (isPrime[i]){
			for (int j = i*i; j < MAX_PRIME; j += i){
				isPrime[j] = false;
			}
		}
	}
	for (int i = 0; i < MAX_PRIME; i++){
		if (isPrime[i]){
			primes.push_back(i);
		}
	}

	long long X;
	cin >> X;

	vpLLLL S;
	factorize(X, primes, S);
	LL sum = 0;
	foreach (factor, S) {
		sum += factor.second;
	}
	cout << sum << endl;
}
