#include "general.h"
#include "primesieve.h"

#define MAX_PRIME 10000000

void getDivisors(vpLLi &factors, vLL &divisors) {
	divisors = { 1 };
	ffor (i, 0, factors.size()) {
		LL f = factors[i].first;
		int count = factors[i].second;
		LL multSum = 1;
		vLL tmp;
		ffor (j, 0, count) {
			multSum *= f;
			vLL c = divisors;
			for_each(c.begin(), c.end(), [multSum](LL &v) {
				v *= multSum;
			});
			tmp.insert(tmp.end(), c.begin(), c.end());
		}
		divisors.insert(divisors.end(), tmp.begin(), tmp.end());
	}
}

void factorize(LL n, vLL &primes, vpLLi &factors) {
	foreach(p, primes) {
		int count = 0;
		while (n % p == 0) {
			n /= p;
			count++;
		}
		if (count > 0){
			factors.pb(mp(p, count));
		}
		if (n == 1){
			break;
		}
	}
	if (n > 1){ 
		factors.pb(mp(n, 1));
	}
}

LL eulerTotientFunction(LL n, vLL &primes) {
	LL total = 1;
	vpLLi factors;
	factorize(n, primes, factors);
	ffor(i, 0, factors.size()) {
		LL factor = factors[i].first;
		int count = factors[i].second;
		total *= factor - 1;
		ffor(j, 1, count){
			total *= factor;
		}
	}
	return total;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vb isPrime(MAX_PRIME / 2, true);
	primeSieve(isPrime, MAX_PRIME);
	vLL primes = { 2 };
	for (int i = 1; i < MAX_PRIME / 2; i++) {
		if (isPrime[i])
			primes.pb(i * 2 + 1);
	}

	int nuoTestCases;
	cin >> nuoTestCases;

	while (nuoTestCases--) {
		LL nuoBlackSquares;
		cin >> nuoBlackSquares;
		vpLLi factors;
		factorize(nuoBlackSquares, primes, factors);
		vLL divisors;
		getDivisors(factors, divisors);
		LL count = 0;
		foreach (d, divisors) {
			count += eulerTotientFunction(nuoBlackSquares / d + 1, primes);
		}
		cout << count << endl;
	}
}
