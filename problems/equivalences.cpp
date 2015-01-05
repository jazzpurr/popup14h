#include "general.h"

stack<int> S;

void strongConnect(vvi &G, vi &visited, vi &lowlink, vi &groupID, int u, int &dfsCount, int &nuoSccGroups) {
	// Set the depth index for u to the smallest unused index
	++dfsCount;
	visited[u] = dfsCount;
	lowlink[u] = dfsCount;
	S.push(u);

	// Consider successors of u
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!visited[v]) {
			// Successor v has not yet been visited; recurse on it
			strongConnect(G, visited, lowlink, groupID, v, dfsCount, nuoSccGroups);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		}
		else if (!groupID[v]){
			// Successor v is in stack S and hence in the current SCC
			lowlink[u] = min(lowlink[u], visited[v]);
		}
	}
	// If v is a root node, pop the stack and generate an SCC
	if (lowlink[u] == visited[u]) {
		nuoSccGroups++;
		while (1) {
			int x = S.top(); S.pop();
			groupID[x] = nuoSccGroups;
			if (x == u) break;
		}
	}
}

int findStrongConnects(vvi &G, vi &groupID, int n) {
	int dfsCount = 0;
	int nuoSccGroups = 0;
	vi visited(G.size(), 0);
	vi lowlink(G.size());
	for (int i = 0; i < n; i++){
		if (!visited[i]) {
			strongConnect(G, visited, lowlink, groupID, i, dfsCount, nuoSccGroups);
		}
	}
	return nuoSccGroups;
}

int main() {
	int nuoTestCases, nuoNodes, nuoEdges;
	scanf("%d", &nuoTestCases);
	while (nuoTestCases--) {
		scanf("%d %d", &nuoNodes, &nuoEdges);
		vvi G(nuoNodes);
		vi groupID(nuoNodes, 0);
		vb in(nuoNodes + 1);
		vb out(nuoNodes + 1);

		int u, v;
		ffor(i, 0, nuoEdges) {
			scanf("%d %d", &u, &v); u--; v--; //0 indexing
			G[u].push_back(v);
		}
		int nuoSccGroups = findStrongConnects(G, groupID, nuoNodes);

		for (int i = 1; i <= nuoSccGroups; i++){
			in[i] = true;
			out[i] = true;
		}
		for (int u = 0; u < nuoNodes; u++){
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (groupID[u] != groupID[v]){
					in[groupID[v]] = false;
					out[groupID[u]] = false;
				}
			}
		}
		int c1 = 0;
		int c2 = 0;
		for (int i = 1; i <= nuoSccGroups; i++) {
			if (in[i]){
				c1++;
			}
			if (out[i]){
				c2++;
			}
		}
		int ans = max(c1, c2);
		if (nuoSccGroups == 1) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}