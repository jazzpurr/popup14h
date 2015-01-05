// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#ifndef MODULAR
#define MODULAR

#include <vector>

//Source: http://en.wikipedia.org/wiki/Modular_arithmetic

//Greatest Common Divisor
long long gcd(long long x, long long y);

// Least Common Multiple
long long lcm(long long x, long long y);

/*
* Finds a,b such that a*x + b*y = gcd(x,y)
* Returns (a,b)
*/
std::pair<long long, long long> euclidean(long long x, long long y);

long long mod(long long x, long long m); // x mod m
long long add_mod(long long x, long long y, long long m); //(x+y) mod m
long long sub_mod(long long x, long long y, long long m); //(x-y) mod m
long long mul_mod(long long x, long long y, long long m); //(x*y) mod m
long long div_mod(long long x, long long y, long long m); //(x/y) mod m


#endif