// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#define _CRT_SECURE_NO_WARNINGS

#include "primesieve.h"
#include <cstdio>

//handles input/output
int main(){
	int maxPrime, nuoQueries, query;
	scanf("%d%d", &maxPrime, &nuoQueries);

	std::vector<bool> isPrime(maxPrime + 1, true); //inits to true, then marks non-primes as false.
	int nuoPrimes = erathostenesSieve(isPrime, maxPrime);
	printf("%d\n", nuoPrimes);

	while (nuoQueries--){
		scanf("%d", &query);
		printf("%d\n", static_cast<int>(isPrime[query])); //prints 1 if true and 0 if false
	}
	return 0;
}