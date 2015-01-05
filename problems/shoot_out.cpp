#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int M = 13;
const double EPS = 1e-9;

int nuoCowboys;
double totalSurvChance[M][(1 << M)][M]; //totalSurvChance[M][(1 << M)+10][M];
double hitChance[M];
int nextCowboys[1 << M][M];
int nuoChances[M][M];
double survChance[M][M], maxSurvChance[M];

bool isZero(double x) {
	if (x > EPS || x < -EPS) return false;
	else return true;
}

//returns next shooter
int getNextCowboy(int state, int x) {
	if (nextCowboys[state][x] != -1) return nextCowboys[state][x];
	int ret = x;
	while (true) {
		if (++ret == nuoCowboys) ret = 0; //overflow, restart from 0
		if (state & (1 << ret)) break; // if ret:th cowboy is alive, go for him
	}
	nextCowboys[state][x] = ret;
	return ret;
}

int nuoLivingCowboys(int state) {
	int ret = 0;
	while (state) {
		ret += state & 1;
		state >>= 1;
	}
	return ret;
}

// god of all dfs
void solver(int state, int curC) {
	if (totalSurvChance[curC][state][0] != -1) return;
	if (nuoLivingCowboys(state) == 1) {
		for (int i = 0; i < nuoCowboys; ++i){
			if (i == curC){	// i is the only one alive
				totalSurvChance[curC][state][i] = 1;
			}else{			// i is dead
				totalSurvChance[curC][state][i] = 0;
			}
		}
		return;
	}

	// opens recursions for every possible state
	for (int i = 0; i < nuoCowboys; ++i) {
		if ((state & (1 << i)) == 0) continue;
		for (int target = getNextCowboy(state, i); target != i; target = getNextCowboy(state, target)) {
			int newState = state ^ (1 << target);
			int newShooter = getNextCowboy(newState, i);
			solver(newState, newShooter);
		}
	}
	//constructs
	for (int i = 0; i < nuoCowboys; ++i){
		for (int j = 0; j < nuoCowboys; ++j) {
			survChance[i][j] = 0; //sum of all chances of survival
			nuoChances[i][j] = 0; //nuo chances
		}
		maxSurvChance[i] = 0;
	}

	for (int i = 0; i < nuoCowboys; ++i) {
		if ((state & (1 << i)) == 0) continue;
		//which target maximises survival chance?
		for (int target = getNextCowboy(state, i); target != i; target = getNextCowboy(state, target)) {
			int newState = state ^ (1 << target);
			int newShooter = getNextCowboy(newState, i);
			maxSurvChance[i] = max(maxSurvChance[i], totalSurvChance[newShooter][newState][i]);
		}
		for (int target = getNextCowboy(state, i); target != i; target = getNextCowboy(state, target)) {
			int newState = state ^ (1 << target);
			int newShooter = getNextCowboy(newState, i);
			if (isZero(maxSurvChance[i] - totalSurvChance[newShooter][newState][i])) { //target gives maximum survival chance to i
				for (int j = 0; j < nuoCowboys; ++j) { //what is this survival chance?
					++nuoChances[i][j];
					survChance[i][j] += totalSurvChance[newShooter][newState][j];

				}
			}
		}
		for (int j = 0; j < nuoCowboys; ++j) {
			survChance[i][j] /= nuoChances[i][j]; //actual chance for survival given current state
		}
	}

	//totalsurvchance = chance for currto survive if hits
	for (int i = 0; i < nuoCowboys; ++i) {
		totalSurvChance[curC][state][i] = hitChance[curC] * survChance[curC][i];
	}

	//  + chance for curr to survive if miss
	for (int i = 0; i < nuoCowboys; ++i) {
		if ((state & (1 << i)) == 0) continue;
		int now = curC;
		double tmp = 1, sum = 0;
		do {
			now = getNextCowboy(state, now);
			sum += tmp * hitChance[now] * survChance[now][i];
			tmp *= (1 - hitChance[now]);
		} while (curC != now);

		totalSurvChance[curC][state][i] += (sum / (1 - tmp)) * (1 - hitChance[curC]);
	}
}
int main() {
	memset(nextCowboys, -1, sizeof(nextCowboys));
	int nuoTestCases;
	scanf("%d", &nuoTestCases);
	while (nuoTestCases--) {
		scanf("%d", &nuoCowboys);
		for (int i = 0; i < nuoCowboys; ++i) {
			scanf("%lf", &hitChance[i]), hitChance[i] /= 100;
		}
		for (int i = 0; i < nuoCowboys; ++i) {
			for (int j = 0; j < (1 << nuoCowboys); ++j) {
				totalSurvChance[i][j][0] = -1;
			}
		}

		solver((1 << nuoCowboys) - 1, 0); //everyone is alive, current cowboy = 0

		for (int i = 0; i < nuoCowboys; ++i) {
			printf("%.9f ", 100 * totalSurvChance[0][(1 << nuoCowboys) - 1][i]);
		}
		printf("\n");
	}
}