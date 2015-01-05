// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <functional>
#include <algorithm>

#include "dijkstra_tt.hpp"

// Time left until this edge can be used given time t, or if negative never again
int edge::t_left(int t) const {
  if (P == 0 or t < t0) // Either only once or t0 hasn't passed
    return t0-t;
  return (P - ((t-t0) % P)) % P; // Next time in timetable
}

// Return distance vector to all nodes, by using Dijkstra's algorithm
// enhanced for timetable on edges
// Nodes that are unreachable get max-int as distance
solution dijkstra_tt(graph g, int source) {
  using namespace std;
  const int n = g.size();
  vector<int> d(n, numeric_limits<int>::max()); // d[…] = inf
  vector<int> p(n, -1); // parents
  p[source] = source;
  d[source] = 0;
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
      if (e.t_left(dist) < 0) // Cannot use anymore
        continue;
      // Min dist to get to v
      if (d[u] + e.d + e.t_left(dist) < d[e.v]) {
        d[e.v] = d[u] + e.d + e.t_left(dist);
        p[e.v] = u;
        // Add all edges to queue
        q.push(make_pair(d[e.v], e.v));
      }
    }
  }
  return solution{d, p};
}

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
