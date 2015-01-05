#include "general.h"

int ans;
#define maxVal 37//37

int countMatches(long st) {
	int cnt = 0;
	for (; st; st >>= 1){
		cnt += (st & 1);
	}
	return cnt;
}


void dfs(int k, int i, long st, int &ans, vl &states) {
	if (k > ans){
		//printf("%i %i\n", i-1, st);
		ans = k;
	}
	for (; i < maxVal; i++){
		if (countMatches(st & states[i]) > k){
			dfs(k + 1, i + 1, st & states[i], ans, states);
		}
	}
}

int main() {
	int nuoTestCases, nuoVases;
	scanf("%d", &nuoTestCases);
	while (nuoTestCases--) {
		scanf("%d", &nuoVases);
		ans = 0;
		vl states(maxVal, 0); //36
		for (int i = 0, shape, decor; i < nuoVases; i++) {
			scanf("%d%d", &shape, &decor), shape--, decor--; //0 idx
			states[shape] |= (1L << decor);
		}
		dfs(0, 0, (1L << maxVal + 1) - 1, ans, states);
		printf("%d\n", ans);
	}
	return 0;
}
