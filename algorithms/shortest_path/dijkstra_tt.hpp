// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>

// Edge in an adjacency list
struct edge {
  // v: other node, t0: first time step, P: interval, d: weight/time
  // If P = 0 then no repeating
  int v, t0, P, d;

  // Time left until this edge can be used given time t, or if negative never again
  int t_left(int t) const;
};

struct solution {
  std::vector<int> distances;
  std::vector<int> parents;
};

typedef std::vector<std::vector<edge>> graph;

// Return distance vector to all nodes, by using Dijkstra's algorithm
// enhanced for timetable on edges
// Nodes that are unreachable get max-int as distance
solution dijkstra_tt(graph g, int source);

// Get trail from source to dest given a parent vector
std::vector<int> get_trail(const std::vector<int> & parents, int destination);
