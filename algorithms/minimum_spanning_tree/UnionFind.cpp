// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#include "UnionFind.h"

// Constructor
UnionFind::UnionFind(int c) {
	p = new int[c + 1];
	d = new int[c + 1];
	for (int i = 1; i <= c; i++) { // 1-indexed
		p[i] = i; // All are singleton-sets with self-parents
		d[i] = 0; // And depth 0
	}
}

UnionFind::~UnionFind() { // Destructor
	delete[] p;
	delete[] d;
}

// Find which segment a node belongs to, the segment is a unique id
int UnionFind::find_top(int x) {
	x++;
	// Until top node (which is its own parent) found, follow the parent
	int curr;
	vector<int> visited;
	for (curr = x; p[curr] != curr; curr = p[curr])
		visited.push_back(curr); // …and remember the trail

	// Now optimize the trail by pointing all to the top
	int top = curr;
	for (auto &curr : visited)
		p[curr] = top;
	return top;
}

bool UnionFind::is_connected(int x, int y) {
	return find_top(x) == find_top(y);
}

void UnionFind::join(int x, int y) {
	int x_root = find_top(x);
	int y_root = find_top(y);
	if (x_root == y_root) // Same segment
		return;

	if (d[x_root] < d[y_root])
		p[x_root] = y_root;
	else if (d[y_root] < d[x_root])
		p[y_root] = x_root;
	else { // Equal depth, must increase
		p[y_root] = x_root;
		d[x_root]++;
	}
}