// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <functional>
#include <algorithm>

#include "dijkstra.hpp"


// Return distance vector to all nodes, by using Dijkstra's algorithm
// Nodes that are unreachable get max-int as distance
solution dijkstra(graph g, int source) {
  using namespace std;
  const int n = g.size();
  vector<int> d(n, numeric_limits<int>::max()); // d[…] = inf
  d[source] = 0;
  vector<int> p(n, -1); // parents
  p[source] = source;
  // pqueue sorted on min dist s.t. first: dist from s to v, where v is second
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  q.push(make_pair(0, source));
  vector<int> visited(n, false);
  while (!q.empty()) {
    int dist = q.top().first, u = q.top().second; q.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    for (const edge &e : g[u]) {
      // Min dist to get to v
      if (d[u] + e.w < d[e.v]) {
        d[e.v] = d[u] + e.w;
        p[e.v] = u;
      }
      // Add all edges to queue
      q.push(make_pair(d[e.v], e.v));
    }
  }
  return solution{d, p};
}

solution dijkstra_tt(graph g, int source);

// Get trail from source to dest given a parent vector
std::vector<int> get_trail(const std::vector<int> & parents, int destination) {
  using namespace std;
  int current = parents[destination];
  int last = destination;
  vector<int> result;
  if (current == -1)
    return result;
  result.push_back(destination);
  while (current != last) {
    result.push_back(current);
    last = current;
    current = parents[current];
  }
  reverse(result.begin(), result.end());
  return result;
}