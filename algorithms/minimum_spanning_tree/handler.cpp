// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include "general.h"
#include "MST.h"

// handles input/output
int main(){
	int nuoNodes, nuoEdges;
	int u, v, w;

	scanf("%i %i", &nuoNodes, &nuoEdges);
	while (nuoNodes != 0 || nuoEdges != 0){
		vector<iiiStruct> edges(nuoEdges);
		ffor(i, 0, nuoEdges){
			scanf("%i %i %i", &u, &v, &w);
			edges[i] = iiiStruct(u, v, w);
		}
		pair<int, vpii> result = mst(edges, nuoNodes);
		int minSpan = result.first;
		vpii resEdges = result.second;
		if (minSpan == INT_INF){
			printf("Impossible\n");
		}
		else{
			printf("%i\n", minSpan);
			for (auto &edge : resEdges){
				printf("%i %i\n", edge.first, edge.second);
			}
		}
		scanf("%i %i", &nuoNodes, &nuoEdges);
	}
	return 0;
}