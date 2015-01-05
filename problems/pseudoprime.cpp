#include "general.h"
#include "primesieve.h"

#define MAX_A 31623

LL big_mod(LL a, int p, int m){
	if (p == 0) return 1; // If power is 0, return 1

	if (p % 2){ // If power odd, Split it : a^p = a * a^(p-1)
		return ((a % m) * (big_mod(a, p - 1, m))) % m;
	}
	else { //If power even, split until odd
		LL c = big_mod(a, p / 2, m);
		return ((c % m) * (c % m)) % m;
	}
}

bool pIsPrime(LL p, vLL &primes){
	ffor(i, 0, primes.size()){
		if (p != primes[i] && p % primes[i] == 0){
			return false;
		}
	}
	return true;
}

int main(){
	vb isPrime(MAX_A + 1, true);
	vLL primes; //will contain the primes between 2 and MAX_A

	primeSieve(primes, isPrime, MAX_A);

	LL p, a;
	scanf("%lld%lld", &p, &a);
	while (p != 0){
		//is pseudoprime if (p isn't prime and a^p == a (mod p))

		if (!pIsPrime(p, primes) && big_mod(a, p, p) == a){
			printf("yes\n");
		}
		else{
			printf("no\n");
		}

		scanf("%lld%lld", &p, &a);
	}
	return 0;
}

