// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

//source http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345

#ifndef SEG_D
#define SEG_D

#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm>

#include "point.hpp"

using namespace std;

struct lineSeg {
	point s, e;
	lineSeg(point _s, point _e) : s(_s), e(_e) {}
};

double min_p_to_l_dist(point p, lineSeg l);

// Given three colinear points p, q, r, checks if q lies on line segment 'pr'
bool isOnSegment(point p, point q, point r);

// To find orientation of ordered triplet (p, q, r).
int orientation(const point& p, const point& q, const point& r);

// returns true if line segment 'l1' and 'l2' intersect.
bool intersects(lineSeg a, lineSeg b);

// calculates the distance between two line segments
double minSegDist(lineSeg a, lineSeg b);


#endif