// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se

#include <cmath>
#include "point.hpp"

point::point(double _x, double _y) : x(_x), y(_y) {}

point point::operator+(const point &other) const {
  return point(x + other.x, y + other.y);
}

point point::operator-(const point &other) const {
  return point(x - other.x, y - other.y);
}

point point::operator*(double c) const {
  return point(x*c, y*c);
}

point point::operator/(double c) const {
  if (c == 0)
    return point();
  else
    return point(x/c, y/c);
}

void point::rotate(double rad) {
  double cosine = cos(-rad);
  double sine = sin(-rad);
  double x_tmp = x * cosine - y * sine;
  y = x * sine + y * cosine;
  x = x_tmp;
}

bool point::operator<  (const point& other) const {
  return x < other.x || (x == other.x && y <  other.y);
}

bool point::operator<= (const point& other) const {
  return x < other.x || (x == other.x && y <= other.y);
}

bool point::operator>  (const point& other) const {
  return x > other.x || (x == other.x && y >  other.y);
}

bool point::operator>= (const point& other) const {
  return x > other.x || (x == other.x && y >= other.y);
}

bool point::operator== (const point& other) const {
  return x == other.x && y == other.y;
}

bool point::operator!= (const point& other) const{
  return !(*this == other);
}

double dist2(const point &a, const point &b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return pow(dx, 2) + pow(dy, 2);
}

double dist(const point &a, const point &b) {
  return sqrt(dist2(a, b));
}

double dot(const point &a, const point &b) {
  return pow(a.x, 2) + pow(b.y, 2);
}
