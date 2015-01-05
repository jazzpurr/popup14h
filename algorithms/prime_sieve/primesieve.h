// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#ifndef PRIMESIEVE
#define PRIMESIEVE

#include <vector>
#include <cmath>

//Erathostenes sieve
//Fills "isPrime" (which is maxPrime big and initialised to true) with false when not prime
//If "i" is a prime, isPrime[i] will contain true, else it will contain false.
//Returns the number of found primes between 0 and maxPrime.
int erathostenesSieve(std::vector<bool> &isPrime, int maxPrime){
	isPrime[0] = false;
	isPrime[1] = false;

	int upperLimit = (int)sqrt(maxPrime); //rounded down
	int nuoPrimes = maxPrime - 1; //assume all except 1 are primes, then decrement

	for (int i = 2; i <= upperLimit; i++) {
		if (isPrime[i]) {
			for (int j = i*i; j <= maxPrime; j += i) {
				if (isPrime[j]){
					nuoPrimes--;
					isPrime[j] = false;
				}
			}
		}
	}
	return nuoPrimes;
}

#endif