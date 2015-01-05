// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#define _CRT_SECURE_NO_WARNINGS

#include "segmentdistance.h"
#include "point.hpp"
#include <cstdio>
#include <algorithm>

int main(){
	int nuoTestCases;
	scanf("%d", &nuoTestCases);

	while (nuoTestCases--){
		int x1, y1, x2, y2, x3, y3, x4, y4;
		scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		lineSeg a(point(x1, y1), point(x2, y2));
		lineSeg b(point(x3, y3), point(x4, y4));

		double segDist = minSegDist(a, b);

		if (abs(segDist) < 5e-3) {
			printf("%.2lf\n", 0.00);
		}
		else{
			printf("%.2lf\n", segDist);
		}
	}

	return 0;
}