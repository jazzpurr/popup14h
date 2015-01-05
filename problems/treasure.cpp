
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

// rotate point clockwise in radians
void rotate(point &p, double rad) {
	double cosine = cos(-rad);
	double sine = sin(-rad);
	double x_tmp = p.x * cosine - p.y * sine;
	p.y = p.x * sine + p.y * cosine;
	p.x = x_tmp;
}

vs directions = {
	"N", "NbE", "NNE", "NEbN", 
	"NE", "NEbE", "ENE", "EbN",
	"E", "EbS", "ESE", "SEbE", 
	"SE", "SEbS", "SSE", "SbE",
	"S", "SbW", "SSW", "SWbS", 
	"SW", "SWbW", "WSW", "WbS",
	"W", "WbN", "WNW", "NWbW", 
	"NW", "NWbN", "NNW", "NbW"
};

int main() {
	map<string, double> dir2rad;
	double to_radians = (2.0 * PI) / directions.size(); // size == 32
	ffor (i, 0, directions.size()){
		dir2rad[directions[i]] = to_radians * i;
	}

	int nuoSteps;
	while (scanf("%d", &nuoSteps), nuoSteps != 0) {
		string dir;
		int dist;

		vector<point> pathTaken;
		point currPos(0, 0);
		ffor(i, 0, nuoSteps){
			cin >> dir >> dist;
			point p(0, dist);
			rotate(p, dir2rad[dir]);
			currPos = currPos + p;
			pathTaken.pb(p);
		}
		double angToNorth;
		scanf("%lf", &angToNorth);
		
		point treasure = currPos;
		rotate(treasure, angToNorth * PI / 180.0); //now treasure is treasure

		currPos = point(0, 0);
		double answer = numeric_limits<double>::max();
		foreach(p, pathTaken) {
			lineSeg l(currPos, currPos + p);
			double distToTreasure = min_p_to_l_dist(l, treasure);
			if (distToTreasure < answer){
				answer = distToTreasure;
			}
			currPos = currPos + p;
		}
		printf("%.2lf\n", answer);
	}

	return 0;
}
