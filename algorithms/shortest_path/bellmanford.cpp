// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>
#include <limits>
#include <stack>

#include <iostream>

#include "bellmanford.hpp"


// Return distance vector to all nodes, by using the Bellman-Ford algorithm
// Nodes that are unreachable get max-int as distance
// Nodes that are reachable by neg. cycles get min-int as distance
solution bellman_ford(graph g, int source) {
  using namespace std;
  const int n = g.size();
  vector<int> d(n, INF); // d[…] = inf
  vector<int> p(n, -1); // Predecessors
  d[source] = 0;
  p[source] = source;
  // pqueue sorted on min dist s.t. first: dist from s to v, where v is second
  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {
      for (const edge &e : g[u]) {
        // Min dist to get to v
        if (d[u] == INF)
          continue;
        if (d[u] + e.w < d[e.v]) {
          d[e.v] = d[u] + e.w;
          p[e.v] = u;
        }
      }
    }
  }
  bool neg_cycles = false;
  stack<int> s; // dfs of nodes
  s.push(source);
  vector<int> visited(n, false);
  while (!s.empty()) {
    int u = s.top(); s.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    for (const edge &e : g[u]) {
      // Min dist to get to e.v
      if (u == e.v and e.w >= 0) // Node to self
        continue;
      if (d[u] + e.w < d[e.v]) {
        neg_cycles = true;
        d[e.v] = NEG_INF;
      }
      s.push(e.v);
    }
  }
  // Make sure to set unreachable nodes to correct parents and distances
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      d[i] = INF;
      p[i] = -1;
    }
  }
  return solution(neg_cycles, d, p);
}
