#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

int prefOutcome[101][8]; // prefOutcome[priestID][state]
int optVote[101][8]; // optVote[priestID][state]
int nuoPriests;

// a kind of dfs
int solve(int priest, int state) {
	if (priest == nuoPriests) return state;  // base case.
	if (optVote[priest][state] != -1) return optVote[priest][state]; //already visited
	bool first = true;
	int bestVote, tmpVote;
	// new recursion for each possible vote
	for (int i = 0; i < 3; ++i) { 
		int newState = (state ^ (1 << i)); // flip i:th bit
		tmpVote = solve(priest + 1, newState);
		if (first) {
			bestVote = tmpVote;
			first = false;
		}
		else if (prefOutcome[priest][tmpVote] < prefOutcome[priest][bestVote]) { // lowest score is best
			bestVote = tmpVote;
		}
	}
	optVote[priest][state] = bestVote;
	return bestVote;
}


int main() {
	int nuoTestCases;
	scanf("%d", &nuoTestCases);
	for (int c = 0; c < nuoTestCases; ++c) {
		memset(optVote, -1, sizeof(optVote));
		scanf("%d", &nuoPriests);
		for (int priest = 0; priest < nuoPriests; ++priest) {
			for (int state = 0; state < 8; ++state) {
				scanf("%d", &prefOutcome[priest][state]);
			}
		}
		int result = solve(0, 0);
		//print result
		for (int i = 2; i >= 0; --i) {
			if (result & (1 << i)) // left to right
				printf("Y");
			else
				printf("N");
		}
		printf("\n");
	}
	return 0;
}