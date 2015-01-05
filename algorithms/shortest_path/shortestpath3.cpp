// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/shortestpath3

#include <iostream>
#include <vector>
#include <limits>

#include "bellmanford.hpp"

using namespace std;

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 1, m, q, s; // #nodes, #edges, #queries, source

  while (true) { // For each test case
    cin >> n >> m >> q >> s;
    if (n == 0) break;
    graph g(n); // Graph, where each el is an adj. list
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w; // u => v with weight w
      g[u].push_back(edge{v, w});
    }
    // Find shortest distances using Dijkstra
    solution sol = bellman_ford(g, s);
    for (int i = 0; i < q; i++) { // Read queries
      int d; // Destination node
      cin >> d;
      vector<int> dist = sol.distances;
      int id = d;
      int distance = dist[d];
      // Backtrack to check for negative cycles
      for (id = d; sol.parents[id] != s and id != -1; id = sol.parents[id]) {
        if (dist[id] == NEG_INF) { // Entered a negative cycle
          distance = dist[id];
          break;
        }
      }
      if (distance == INF)
        cout << "Impossible" << endl;
      else if (distance == NEG_INF)
        cout << "-Infinity" << endl;
      else
        cout << distance << endl;
    }
    cout << endl;
  }
}
