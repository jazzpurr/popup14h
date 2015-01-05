// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#ifndef GEN_CHIN_REM
#define GEN_CHIN_REM

#include "modular.h"

// returns x so that "x = a (mod n)" and "x = b (mod m)"
long long chineseRemainder(long long a, long long n, long long b, long long m, long long K);

// returns x, K so that "x = a (mod n)" and "x = b (mod m)", with "K = lcm(n, m)"
// if impossible, returns "-1, -1"
std::pair<long long, long long> generalChineseRemainder(long long a, long long n, long long b, long long m);

#endif