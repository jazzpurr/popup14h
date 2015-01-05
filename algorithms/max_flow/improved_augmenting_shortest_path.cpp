// source: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=maxFlowRevisited

#include "general.h"

int reverseBFS(vvll &capM, vl &dist, vi &nuoNodesWithDist, int nuoNodes, int sink)  {
    int i, j;

	for (i = 1; i <= nuoNodes; i++){
		nuoNodesWithDist[dist[i] = nuoNodes] ++;
	}

	nuoNodesWithDist[nuoNodes]--;
	dist[sink] = 0;
	nuoNodesWithDist[0]++;

	queue<int> Q;
	Q.push(sink);

	while (!Q.empty())  {
		i = Q.front(); Q.pop();
		for (j = 1; j <= nuoNodes; j++)  {
			if (dist[j] < nuoNodes || capM[j][i] == 0)  continue;

			Q.push(j);

			nuoNodesWithDist[nuoNodes]--;
			dist[j] = dist[i] + 1;
			nuoNodesWithDist[dist[j]]++;

		}
	}

	return 0;
}

int augment(vvll &capM, vvll &flowM, vi &parent, int source, int sink)  {
	int i, j;
	long long tmp, width(LLONG_MAX);

	for (i = sink, j = parent[i]; i != source; i = j, j = parent[j])  {
		tmp = capM[j][i];
		if (tmp < width)  width = tmp;
	}

	for (i = sink, j = parent[i]; i != source; i = j, j = parent[j])  {
		capM[j][i] -= width;  flowM[j][i] += width;
		capM[i][j] += width;  flowM[i][j] -= width;
	}

	return width;
}

int retreat(vvll &capM, vl &dist, vi &parent, vi &nuoNodesWithDist, int nuoNodes, int source, int &i)  {
	int tmp;
	int j, mind(nuoNodes - 1);

	for (j = 1; j <= nuoNodes; j++){
		if (capM[i][j] > 0 && dist[j] < mind){
			mind = dist[j];
		}
	}

	tmp = dist[i];

	nuoNodesWithDist[dist[i]]--;
	dist[i] = 1 + mind;
	nuoNodesWithDist[dist[i]]++;

	if (i != source) {
		i = parent[i];
	}

	return nuoNodesWithDist[tmp];
}

long long getTotalFlow(vvll &capM, vvll &flowM, int nuoNodes, int source, int sink)  {
	int i, j;
	int totalFlow = 0;

	vl dist(nuoNodes + 1);
	vi parent(nuoNodes + 1);
	vi nuoNodesWithDist(nuoNodes + 1);
	vi currArc(nuoNodes + 1);

	reverseBFS(capM, dist, nuoNodesWithDist, nuoNodes, sink);

	for (i = 1; i <= nuoNodes; i++){
		currArc[i] = 1;
	}

	i = source;
	while (dist[source] < nuoNodes)  {
		for (j = currArc[i]; j <= nuoNodes; j++){
			if (capM[i][j] > 0 && dist[i] == dist[j] + 1){
				break;
			}
		}

		if (j <= nuoNodes)  {
			currArc[i] = j;
			parent[j] = i;
			i = j;

			if (i == sink)  {
				totalFlow += augment(capM, flowM, parent, source, sink);  // Augment the flow
				i = source;
			}
		}
		else  {
			currArc[i] = 1;
			if (retreat(capM, dist, parent, nuoNodesWithDist, nuoNodes, source, i) == 0){
				break;
			}
		}
	}
	return totalFlow;
}


int main() {
	int nuoNodes, nuoEdges, source, sink;
	int u, v, c;

	scanf("%i %i %i %i", &nuoNodes, &nuoEdges, &source, &sink);

	vvll capM(nuoNodes + 1, vll(nuoNodes + 1, 0));
	vvll flowM(nuoNodes + 1, vll(nuoNodes + 1, 0));

	ffor(i, 0, nuoEdges){
		scanf("%i %i %i", &u, &v, &c);
		if (u != v){
			capM[u + 1][v + 1] += c;
		}
	}
	long long totalFlow = getTotalFlow(capM, flowM, nuoNodes, source + 1, sink + 1);

	int nuoUsedEdges = 0;
	ffor(i, 1, nuoNodes + 1){
		ffor(j, 1, nuoNodes + 1){
			if (flowM[i][j] > 0) {
				nuoUsedEdges++;
			}
		}
	}
	printf("%i %lld %i\n", nuoNodes, totalFlow, nuoUsedEdges);
	ffor(i, 1, nuoNodes + 1){
		ffor(j, 1, nuoNodes + 1){
			if (flowM[i][j] > 0) {
				printf("%i %i %lld\n", i - 1, j - 1, flowM[i][j]);
			}
		}
	}
	return 0;
}