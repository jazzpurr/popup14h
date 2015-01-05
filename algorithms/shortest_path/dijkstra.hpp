// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>

// Edge in an adjacency list
struct edge {
  int v, w; // v: other node, w: weight
};

struct solution {
  std::vector<int> distances;
  std::vector<int> parents;
};

typedef std::vector<std::vector<edge>> graph;

// Return distance vector to all nodes, by using Dijkstra's algorithm
// Nodes that are unreachable get max-int as distance
solution dijkstra(graph g, int source);

// Get trail from source to dest given a parent vector
std::vector<int> get_trail(const std::vector<int> & parents, int destination);
