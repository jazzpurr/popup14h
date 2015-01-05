// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include "floyd_warshall.h"


// calculates the minimum distances between each node and returns
// the result as a matrix. -Infinity will be marked as INT_NINF and unreachable as INT_INF
vvi floydWarshall(iGraph &graph, int nuoNodes){
	vvi distM = vvi(nuoNodes, vi(nuoNodes, INT_INF));

	//creates basic distM from input
	ffor(i, 0, nuoNodes){
		distM[i][i] = 0;
	}
	ffor(u, 0, nuoNodes){
		foreach(edge, graph[u]){
			int v = (*edge).first;
			int w = (*edge).second;
			if (u == v){
				distM[u][v] = min(0, w);
			}
			else{
				distM[u][v] = w;
			}
		}
	}


	//solves for distances between all nodes
	ffor(k, 0, nuoNodes){
		ffor(i, 0, nuoNodes){
			ffor(j, 0, nuoNodes){
				if (distM[i][k] != INT_INF && distM[k][j] != INT_INF) {
					if (distM[i][j] > distM[i][k] + distM[k][j]){ //if there is a path ik + kj that costs less than ij, update dist[ij]
						distM[i][j] = distM[i][k] + distM[k][j];
					}
				}
			}
		}
	}
	//marks neginf loops
	ffor(i, 0, nuoNodes){
		ffor(j, 0, nuoNodes){
			ffor(k, 0, nuoNodes){
				if (distM[i][k] != INT_INF && distM[k][j] != INT_INF && distM[k][k] < 0){    // If all are true then the path from i to j is undefined
					distM[i][j] = INT_NINF;													// because one of the nodes has a neg dist to itself.
				}
			}
		}
	}

	return distM;
}