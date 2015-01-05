// Author: Didrik Nordström, didrikn@kth.se
// https://kth.kattis.com/problems/shortestpath2

#include <iostream>
#include <vector>
#include <limits>

#include "dijkstra_tt.hpp"

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
      int u, v, t0, P, d;
      cin >> u >> v >> t0 >> P >> d;
      g[u].push_back(edge{v, t0, P, d});
    }
    // Find shortest distances using Dijkstra
    solution sol = dijkstra_tt(g, s);
    for (int i = 0; i < q; i++) { // Read queries
      int d; // Destination node
      cin >> d;
      if (sol.distances[d] == numeric_limits<int>::max())
        cout << "Impossible" << endl;
      else
        cout << sol.distances[d] << endl;
      //vector<int> path = get_trail(sol.parents, d);
      //for (auto &step : path)
      //  cout << step << " > ";
      //cout << endl;
    }
    cout << endl;
  }
}
