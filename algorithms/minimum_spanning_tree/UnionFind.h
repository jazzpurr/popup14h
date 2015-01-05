// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#ifndef UNIONFIND
#define UNIONFIND

#include "general.h"

// A set of c 1-indexed nodes which are disjunct from eachother.
// There are 2 operations, join and find which joins sections of
// the graph and checks if they are connected.
class UnionFind {

private:
	int *p, *d; // Parent pointers and depths
	int find_top(int x);

public:

	// Constructor, c: cardinality of set
	UnionFind(int c);
	~UnionFind(); // Destructor

	// Join two nodes together, their segments will be joined respectively
	void join(int x, int y);

	// Find out if the nodes are connected
	bool is_connected(int x, int y);

};

#endif // header guard