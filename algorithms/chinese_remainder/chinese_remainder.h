// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#ifndef CHIN_REM
#define CHIN_REM

#include "modular.h"

// returns x so that "x = a (mod n)" and "x = b (mod m)"
// If you have more than two arguments, call repeatedly.
long long chineseRemainder(long long a, long long n, long long b, long long m, long long K){
	std::pair<long long, long long> uv = euclidean(n, m);
	long long u = mod(uv.first, m);
	long long v = mod(uv.second, n);

	/*
	K = n*m
	u*n + v*m = gcd(n,m) = 1
=>
	u*n = 1 - v*m  =>	u*n (mod n) = 0
						u*n (mod m) = 1
=>
	a*v*m + b*u*n (mod n) = a*v*m (mod n) = a * (1-u*n) (mod n) = a
	a*v*m + b*u*n (mod m) = b*u*n (mod m) = b * (1-v*m) (mod m) = b
=>
	x = a*v*m + b*u*n (mod K)
	*/

	long long x = add_mod(mul_mod(mul_mod(a, v, K), m, K), mul_mod(mul_mod(b, u, K), n, K), K);
	return x;
}

#endif