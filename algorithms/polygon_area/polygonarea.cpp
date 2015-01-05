// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/polygonarea

#include <iostream>
#include <vector>
#include <cmath>
#include "point.hpp"

using namespace std;

double polygon_area(const vector<point> &poly) {
  double area = 0;
  for (int i = 0; i < poly.size(); i++) {
    int j = (i+1) % poly.size();
    area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
  }
  area /= 2;
  return area;
}

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(1);

  int N; // # vertices

  while (cin >> N, N > 0) {
    vector<point> polygon;
    while (N--) {
      double x, y;
      cin >> x >> y;
      polygon.push_back(point(x, y));
    }
    double area = polygon_area(polygon);
    if (area >= 0)
      cout << "CCW " << fixed << area << endl;
    else
      cout << "CW " << fixed << -area << endl;
  }
}
