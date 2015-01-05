// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se
//
// https://kth.kattis.com/problems/unionfind

#include <cstdio>
#include "join_set.h"

using namespace std;


// Solves the union-find problem
int main() {

  int n_elements; // Elements in the base set
  int n_ops; // Number of operations
  char op; // Current op
  int x, y; // Current operands
  scanf("%i %i\n", &n_elements, &n_ops);

  join_set set(n_elements); // Custom join_set object

  while (n_ops--) { // For every operation
    scanf("%c %i %i\n", &op, &x, &y); // Read operator and operands

    if (op == '?') // Query if x and y are connected
      printf(set.is_connected(x, y) ? "yes\n" : "no\n");
    else if (op == '=') // Join x and y
      set.join(x, y);
  }
  
}
