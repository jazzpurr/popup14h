// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#ifndef FLOYDWARSHALL
#define FLOYDWARSHALL

#include "general.h"

// calculates the minimum distances between each node and returns
// the result as a matrix. -Infinity will be marked as INT_NINF and unreachable as INT_INF
vvi floydWarshall(iGraph &graph, int nuoNodes);

#endif // header guard