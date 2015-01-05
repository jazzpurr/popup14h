// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#ifndef MST
#define MST

#include "general.h"
#include "UnionFind.h"

//just carries 3 ints, (edge)
struct iiiStruct {
	int u, v, w;
	iiiStruct(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {} // Constructor
	iiiStruct() : iiiStruct(0, 0, 0) {} // Default constructor
};

// Finds the MST of the input edges.
// Sorts by weight, then goes through them in order, and  
// new vertices to the union , and new valid edges
// to the output MST, and increases sum.
// Finally sorts MST and returns sum + MST
pair<int, vpii> mst(vector<iiiStruct> &edges, int nuoNodes);


#endif
