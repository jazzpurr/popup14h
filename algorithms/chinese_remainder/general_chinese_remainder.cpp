// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

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


// returns (x, K) so that "x = a (mod n)" and "x = b (mod m)", with "K = lcm(n, m)"
// if impossible, returns (-1, -1)
std::pair<long long, long long> generalChineseRemainder(long long a, long long n, long long b, long long m){
	long long x, K;
	long long d = gcd(n, m);

	if (d == 1){ //normal chinese remainder
		K = n*m;
		x = chineseRemainder(a, n, b, m, K);
	}

	else if (d > 1){ //general chinese remainder

		K = lcm(n, m);
		long long c;
		if (b < a){ // c can't be negative in our program
			c = sub_mod(a, b, K + 1);
		}
		else{
			c = sub_mod(b, a, K + 1);
		}
		if (mod(c, d) == 0){ // d|c
			long long K2 = div_mod(K, d, K + 1);
			long long n2 = div_mod(n, d, K + 1);
			long long m2 = div_mod(m, d, K + 1);
			long long c2 = div_mod(c, d, K + 1);
			long long x3;

			//x = d * x3 + a (mod d * n2 * m2) = d * x3 + a (mod K)

			if (b < a){
				x3 = chineseRemainder(c2, n2, 0, m2, K2);
				x = add_mod(mul_mod(x3, d, K), b, K);
			}
			else{
				x3 = chineseRemainder(0, n2, c2, m2, K2);
				x = add_mod(mul_mod(x3, d, K), a, K);
			}
		}

		else{ // !(d|c)
			x = -1;
			K = -1;
		}
	}

	return std::make_pair(x, K);
}