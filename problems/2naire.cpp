#include "general.h"

double solver(int n, double t, vd &twoPow){
	if (fabs(1 - t) < 1e-9){ // t == 1
		return twoPow[n];
	}

	double answer = twoPow[n];
	rfor (i, n - 1, 0) {
		double f = twoPow[i] / answer;
		if (f <= t){
			answer = ((1 + t) / 2) * answer;
		}
		else{
			answer = (((f - t) / (1 - t)) * twoPow[i]) + (((1 - f) / (1 - t)) * ((1 + f) / 2) * answer);
		}
	}
	return answer;
}

int main() {
	// precalc
	vd twoPow(31);
	twoPow[0] = 1;
	ffor(i, 1, 31){
		twoPow[i] = twoPow[i - 1] * 2;
	}

	// main
	int n;
	double t;
	while (scanf("%d %lf", &n, &t), n) {
		printf("%0.3lf\n", solver(n, t, twoPow));
	}

	return 0;
}