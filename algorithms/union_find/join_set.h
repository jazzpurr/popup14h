
// A set of c 1-indexed nodes which are disjunct from eachother.
// There are 2 operations, join and find which joins sections of
// the graph and checks if they are connected.
class join_set {

private:
  int *p, *d; // Parent pointers and depths
  int find_top(int x);

public:

  // Constructor, c: cardinality of set
  join_set(int c);
  ~join_set(); // Destructor

  // Join two nodes together, their segments will be joined respectively
  void join(int x, int y);

  // Find out if the nodes are connected
  bool is_connected(int x, int y);

};
