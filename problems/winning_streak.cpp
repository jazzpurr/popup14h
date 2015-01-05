#include "general.h"

// mwsProb = odds of maxWinStreak j in i consecutive games
// pPow = p^i
double solver(int n, double p){
	vvd mwsProb(n + 1, vd(n + 1));
	vd pPow(n + 1);
	pPow[0] = 1.0;
	ffor (i, 1, n+1){
		pPow[i] = pPow[i - 1] * p;
	}

	ffor (j, 0, n+1){
		mwsProb[0][j] = 1.0;
	}

	ffor(i, 1, n + 1){
		ffor(j, 0, n + 1){
			mwsProb[i][j] = mwsProb[i - 1][j];

			if (j == i - 1){
				mwsProb[i][j] -= pPow[i];
			}
			else if (j < i - 1){
				mwsProb[i][j] -= mwsProb[i - j - 2][j] * (1 - p) * pPow[j + 1];
			}
		}
	}
	double answer = 0.0;
	ffor (j, 1, n+1){
		//printf("%lf %lf\n", mwsProb[n][j], mwsProb[n][j - 1]);
		answer += j * (mwsProb[n][j] - mwsProb[n][j - 1]);
	}
	return answer;
}

int main(){
	int n;
	double p;
	while (scanf("%d %lf", &n, &p) != EOF) {
		printf("%lf\n", solver(n, p));
	}

	return 0;
}