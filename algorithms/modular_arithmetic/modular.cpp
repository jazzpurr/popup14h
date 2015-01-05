// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#include <cmath>
#include <vector>

//Source: http://en.wikipedia.org/wiki/Modular_arithmetic

// x mod m
long long mod(long long x, long long m){
	if ((x % m) < 0){
		return (x % m + m);
	}
	else{
		return (x % m);
	}
}

/*
* Finds a,b such that a*x + b*y = gcd(x,y)
* @return (a,b)
*/
std::pair<long long, long long> euclidean(long long x, long long y){
	if (x == 0){
		return std::make_pair(0, 1);
	}
	else if (y == 0) {
		return std::make_pair(1, 0);
	}
	else{
		std::pair<long long, long long> ba = euclidean(y, mod(x, y));
		long long a = ba.second;
		long long b = ba.first;
		return std::make_pair(a, b - (x / y) * a);
	}
}


/*
* (x+y) mod m
*/
long long add_mod(long long x, long long y, long long m){
	long long z = x + y;
	if (z >= m){
		z = z - m;
	}
	if (z < 0){
		return z + m;
	}
	else{
		return z;
	}
}


/*
* (x-y) mod m
*/
long long sub_mod(long long x, long long y, long long m){
	long long z;
	if (y > x){
		z = m + x - y;
	}
	else{
		z = x - y;
	}
	if (z < 0){
		return z + m;
	}
	else{
		return z;
	}
}

/*
* (x*y) mod m
*/
long long mul_mod(long long x, long long y, long long m){
	long long z = 0;
	while (y != 0) {
		//printf("%d %d %d\n", x, y, z);
		if (mod(y, 2) != 0) {
			z = add_mod(z, x, m);
		}
		x = add_mod(x, x, m);
		y = y / 2;
	}
	if (z < 0){
		return z + m;
	}
	else{
		return z;
	}
}

/*
* (x/y) mod m
*/
long long div_mod(long long x, long long y, long long m) {
	std::pair<long long, long long> ab = euclidean(y, m); // gets y^-1
	long long a = ab.first;
	long long b = ab.second;
	if ((a*y + b*m) != 1) {
		return -1;	//no inverse exist
	}
	a = mod(a, m);
	return mul_mod(x, a, m);
}