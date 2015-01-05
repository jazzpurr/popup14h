// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

//source http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345

#include "segmentdistance.h"

double min_p_to_l_dist(point p, lineSeg l){
	if (l.s == l.e)	return dist(p, l.s);
	

	double segment_size = dist(l.s, l.e);
	double u = ((p.x - l.s.x)*(l.e.x - l.s.x) + (p.y - l.s.y)*(l.e.y - l.s.y)) / (segment_size*segment_size);

	double x = l.s.x + u*(l.e.x - l.s.x);
	double y = l.s.y + u*(l.e.y - l.s.y);
	point projection(x, y);
	double line_projection_dist = dist(p, projection);

	if (dist(projection, l.s) + dist(projection, l.e) - dist(l.s, l.e) > 1e-8){ // projection not on segment
		line_projection_dist = 1e9;
	}

	double end1_dist = dist(p, l.s);
	double end2_dist = dist(p, l.e);

	double result = min({ line_projection_dist, end1_dist, end2_dist });
	return result;
}

// Given three colinear points p, q, r, checks if q lies on line segment 'pr'
bool isOnSegment(point p, point q, point r){
	if (p.x <= max(q.x, r.x) && p.x >= min(q.x, r.x) && p.y <= max(q.y, r.y) && p.y >= min(q.y, r.y))
	{
		return true;
	}
	return false;
}

// To find orientation of ordered triplet (p, q, r).
int orientation(const point& p, const point& q, const point& r){
	int orientation = (int)((q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y));
	if (orientation == 0) return 0;
	return (orientation > 0) ? 1 : -1; // clockwise or counterclockwise
}

// returns true if line segment 'l1' and 'l2' intersect.
bool intersects(lineSeg l1, lineSeg l2){
	vector<point> ans;
	point a = l1.s, b = l1.e, c = l2.s, d = l2.e;

	if (orientation(a, b, c) == 0 && orientation(a, b, d) == 0 && orientation(c, d, a) == 0 && orientation(c, d, b) == 0) { // all points colinear
		// order the points
		point min_l1 = min(a, b);
		point max_l1 = max(a, b);
		point min_l2 = min(c, d);
		point max_l2 = max(c, d);

		if (min_l1 < min_l2){
			if (max_l1 < min_l2){ // disjoint
				return false;
			}
		}
		else if (min_l2 < min_l1){
			if (max_l2 < min_l1){ // disjoint
				return false;
			}
		}
		else{ //overlap
			return true;
		}
	}

	else{
		double x1 = (b.x - a.x);
		double y1 = (b.y - a.y);
		double x2 = (d.x - c.x);
		double y2 = (d.y - c.y);
		double s = (-y1*(a.x - c.x) + x1*(a.y - c.y)) / (-x2*y1 + x1*y2);
		double t = (x2*(a.y - c.y) - y2*(a.x - c.x)) / (-x2*y1 + x1*y2);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1){ // collision
			return true;
		}
		else {
			return false;
		}
	}
}

// calculates the distance between two line segments
double minSegDist(lineSeg a, lineSeg b){
	// if segments intersect, distance is 0
	// else distance is shortest distance between endpoints and other segment
	if (!intersects(a, b)){
		double ans = min({
			min_p_to_l_dist(a.s, b),
			min_p_to_l_dist(a.e, b),
			min_p_to_l_dist(b.s, a),
			min_p_to_l_dist(b.e, a)
		});
		return ans;
	}
	return 0.0;
}