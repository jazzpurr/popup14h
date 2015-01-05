#include "general.h"

#define MAX_PRIME 47000 // ~sqr 2^31

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

LL nuo_p_in_n(LL n, LL p){
	LL count = 0;
	while (n >= p){
		count += n / p;
		n /= p;
	}
	return count;
}

int main(){
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

	//main alg
	long long  n, m;
	while (scanf("%lld %lld", &n, &m) != EOF){
		if (m == 1){
			printf("%lld divides %lld!\n", m, n);
		}
		else if (m == 0){
			printf("%lld does not divide %lld!\n", m, n);
		}

		else{
			vpLLLL S;
			factorize(m, primes, S); //factorizes m into S
			bool f = 0;
			for (int i = 0; i < S.size(); i++){
				int primepower = nuo_p_in_n(n, S[i].first);
				if (primepower < S[i].second){ 
					f = 1; 
					break; }
			}
			if (!f){
				printf("%lld divides %lld!\n", m, n);
			}
			else{
				printf("%lld does not divide %lld!\n", m, n);
			}
		}
	}
	return 0;

}