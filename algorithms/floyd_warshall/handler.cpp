// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include "general.h"
#include "floyd_warshall.h"

// handles input/output
int main(){
	int nuoNodes, nuoEdges, nuoQueries;
	int u, v, w;

	scanf("%i %i %i", &nuoNodes, &nuoEdges, &nuoQueries);
	while (nuoNodes != 0 || nuoEdges != 0 || nuoQueries != 0){
		iGraph graph(nuoNodes);

		ffor(i, 0, nuoEdges){
			scanf("%i %i %i", &u, &v, &w);
			bool duplicate = false;
			foreach(edge, graph[u]){
				if ((*edge).first == v){
					duplicate = true;
					if ((*edge).second > w){
						(*edge).second = w;
					}
				}
			}
			if (!duplicate){
				graph[u].pb(mp(v, w));
			}
		}

		vvi distM = floydWarshall(graph, nuoNodes);

		ffor(i, 0, nuoQueries) {
			scanf("%i %i", &u, &v);
			if (distM[u][v] == INT_INF){
				printf("Impossible\n");
			}
			else if (distM[u][v] == INT_NINF){
				printf("-Infinity\n");
			}
			else{
				printf("%i\n", distM[u][v]);
			}
		}
		printf("\n");
		scanf("%i %i %i", &nuoNodes, &nuoEdges, &nuoQueries);
	}
	return 0;
}