// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include "MST.h"

// Finds the MST of the input edges.
// Sorts by weight, then goes through them in order, and  
// new vertices to the union , and new valid edges
// to the output MST, and increases sum.
// Finally sorts MST and returns sum + MST
pair<int, vpii> mst(vector<iiiStruct> &edges, int nuoNodes){
	UnionFind UF(nuoNodes);

	sort(all(edges), [](iiiStruct x, iiiStruct y){ return x.w < y.w; });
	vpii resMST;
	int sum = 0;
	int count = 1;

	for (auto &edge : edges){
		if (edge.u != edge.v){
			if (!UF.is_connected(edge.u, edge.v)){
				if (edge.u > edge.v){
					resMST.pb(mp(edge.v, edge.u));
				}
				else{
					resMST.pb(mp(edge.u, edge.v));
				}
				UF.join(edge.u, edge.v);
				sum += edge.w;
				count++;
			}
		}
	}

	sort(all(resMST), [](pii x, pii y){
		return x.first < y.first || (x.first == y.first && x.second < y.second);
	});

	if (count != nuoNodes) {
		return mp(INT_INF, resMST);
	}

	else {
		return mp(sum, resMST);
	}
}