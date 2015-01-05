// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se

#ifndef POINT_HPP
#define POINT_HPP

/* Vector of 2 elements, x and y */

struct point {
  double x, y;

  // constructor
  point(double _x = 0, double _y = 0);

  // add and subtract vectors
  point operator+(const point &other) const;
  point operator-(const point &other) const;

  // scale vector
  point operator*(double c) const;
  point operator/(double c) const;

  // rotate vector in radians clockwise
  void rotate(double rad);

  // comparisons
  bool operator<  (const point& other) const;
  bool operator<= (const point& other) const;
  bool operator>  (const point& other) const;
  bool operator>= (const point& other) const;
  bool operator== (const point& other) const;
  bool operator!= (const point& other) const;
};

/* Common vector operations */

// distance squared, high performance
double dist2(const point &a, const point &b);

// real distance, slightly slower
double dist(const point &a, const point &b);

// dot (scalar) product
double dot(const point &a, const point &b);

#endif
