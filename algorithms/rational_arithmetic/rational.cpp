
#include "rational.hpp"

#include <iostream>
#include <algorithm>

/* Greatest common denominator, works with negatives */

long gcd(long u, long v) {
  while (v != 0) {
    long r = u % v;
    u = v;
    v = r;
  }
  return u;
}

/* Private methods */

void rational::normalize() {
  long g;
  do {
    g = gcd(n, d);
    n /= g;
    d /= g;
  } while (g != 1);
  if (d < 0) {
    n *= -1;
    d *= -1;
  }
}

long rational::cmp(const rational &other) const {
  return n*other.d - other.n*other.d;
}

/* Constructors */

rational::rational()
  : rational(0, 1)
{ }

rational::rational(long _n, long _d)
  : n(_n)
  , d(_d)
{
  normalize();
}

/* Arithmetic */

rational rational::operator+(const rational &other) const {
  rational copy = *this;
  copy.n *= other.d;
  copy.n += other.n * copy.d; // TODO
  copy.d *= other.d;
  copy.normalize();
  return copy;
}

rational rational::operator-(const rational &other) const {
  rational copy = other;
  copy.n *= -1;
  return *this + copy;
}

rational rational::operator*(const rational &other) const {
  rational copy = *this;
  copy.n *= other.n;
  copy.d *= other.d;
  copy.normalize();
  return copy;
}

rational rational::operator/(const rational &other) const {
  rational copy = other;
  std::swap(copy.n, copy.d); // Inverse
  return (*this) * copy;
}

/* Comparisons */

bool rational::operator==(const rational &other) const {
  return cmp(other) == 0;
}

bool rational::operator!=(const rational &other) const {
  return cmp(other) != 0;
}

bool rational::operator<(const rational &other) const {
  return cmp(other) < 0;
}

bool rational::operator<=(const rational &other) const {
  return cmp(other) <= 0;
}

bool rational::operator>(const rational &other) const {
  return cmp(other) > 0;
}

bool rational::operator>=(const rational &other) const {
  return cmp(other) >= 0;
}

/* I/O */

std::ostream& operator<<(std::ostream &os, const rational &r) {
  os << r.n << " / " << r.d;
  return os;
}

std::istream& operator>>(std::istream &is, rational &r) {
  is >> r.n >> r.d;
  r.normalize();
  return is;
}
