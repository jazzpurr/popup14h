#include "general.h"

//inspired by stack overflow "shortest distance between point and line segment"
struct point {
	double x, y;
	point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

	point operator+(const point &b) const {
		return point(x + b.x, y + b.y);
	}

	point operator-(const point &b) const {
		return point(x - b.x, y - b.y);
	}

	point operator*(double c) const {
		return point(x*c, y*c);
	}
};

struct lineSeg {
	point s, e;
	lineSeg(point _s, point _e) : s(_s), e(_e) {}
};

double p_distSqr(point &a, point &b){
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return dx*dx + dy*dy;
}

double p_dist(point &a, point &b) {
	return sqrt(p_distSqr(a, b));
}

double dot_product(const point &p1, const point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double min_p_to_l_dist(lineSeg &l, point &p){
	double dSqr = p_distSqr(l.s, l.e);
	double t = dot_product(p - l.s, l.e - l.s) / dSqr;
	if (t < 0.0){
		return p_dist(p, l.s);
	}
	else if (t > 1.0){
		return p_dist(p, l.e);
	}
	point projection = l.s + (l.e - l.s) * t;
	return p_dist(p, projection);
}

int main(){
	int nuoTestCases, nuoInnerPoints, nuoOuterPoints;
	scanf("%d", &nuoTestCases);

	while (nuoTestCases--){
		scanf("%d", &nuoInnerPoints);
		vector<point> innerPoints(nuoInnerPoints);
		ffor(i, 0, nuoInnerPoints){
			scanf("%lf%lf", &innerPoints[i].x, &innerPoints[i].y);
		}
		scanf("%d", &nuoOuterPoints);
		vector<point> outerPoints(nuoOuterPoints + 1); //+1 because circling, last followed by first
		ffor(i, 0, nuoOuterPoints){
			scanf("%lf%lf", &outerPoints[i].x, &outerPoints[i].y);
		}
		outerPoints[nuoOuterPoints] = outerPoints[0];
		double answer = numeric_limits<double>::max();
		ffor(i, 0, nuoInnerPoints){
			ffor(j, 0, nuoOuterPoints){
				lineSeg l(outerPoints[j], outerPoints[j + 1]);
				double width = min_p_to_l_dist(l, innerPoints[i]);
				if (width < answer){
					answer = width;
				}
			}
		}
		printf("%.6f\n", answer / 2); //answer = max allowed diagonal, we want max allowed radius
	}

	return 0;
}
