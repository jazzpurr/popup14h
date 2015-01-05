#include "general.h"

// Edge in an adjacency list
struct edge {
	int v; // other node
	double f; // factor between 0 and 1
};

typedef std::vector<std::vector<edge>> graph;

vector<double> dijkstra(graph g, int source) {
	using namespace std;
	const int n = g.size();
	vector<double> d(n, 0); // d[...] = 0
	d[source] = 1.0; // Full health
	// pqueue sorted on max dist
	priority_queue<pair<double, int>> q;
	q.push(make_pair(d[source], source));
	vector<int> visited(n, false);
	while (!q.empty()) {
		//double dist = q.top().first;
		int u = q.top().second;
		q.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (const edge &e : g[u]) {
			double new_dist = d[u] * e.f;
			if (new_dist > d[e.v]) {
				d[e.v] = d[u] * e.f;
				// Add all edges to queue
				q.push(make_pair(d[e.v], e.v));
			}
		}
	}
	return d; // Empty parents
}

int main() {
	int nuoNodes, nuoEdges; // #nodes, #edges
	cin >> nuoNodes >> nuoEdges;
	while (nuoNodes != 0){
		graph g(nuoNodes);
		for (int i = 0; i < nuoEdges; i++) {
			int u, v;
			double f; // factor
			scanf("%i %i %lf", &u, &v, &f);
			g[u].push_back(edge{ v, f });
			g[v].push_back(edge{ u, f });
		}
		vector<double> dist = dijkstra(g, 0);
		printf("%.4f\n", dist[nuoNodes - 1]);

		cin >> nuoNodes >> nuoEdges;
	}
}