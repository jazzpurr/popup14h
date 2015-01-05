// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include <vector>
#include <limits>

#define INF     (numeric_limits<int>::max())
#define NEG_INF (numeric_limits<int>::min())

// Edge in an adjacency list
struct edge {
  int v, w; // v: other node, w: weight
};

struct solution {
  bool status;
  std::vector<int> distances;
  std::vector<int> parents;
  solution(bool s, std::vector<int> d = std::vector<int>(), std::vector<int> p = std::vector<int>())
    : status(s), distances(d), parents(p) {}
};

typedef std::vector<std::vector<edge>> graph;

// Return distance vector to all nodes, by using the Bellman-Ford algorithm
// Nodes that are unreachable get max-int as distance
solution bellman_ford(graph g, int source);
