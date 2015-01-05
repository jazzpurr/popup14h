
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

class rational {
  long n; // numerator
  long d; // denominator

  // Runs GCD, and makes sure the denominator is positive
  void normalize();

  // Compare this to another rational number "other":
  // - if negative then this is smaller
  // - if positive then this is larger
  // - if 0 they are equal
  long cmp(const rational &other) const;

public:

  // Default constructor, creates 1 / 0
  rational();

  // Parameter constructor, creates _n / _d and normalizes
  rational(long _n, long _d);

  // These return a new normalized rational number
  rational operator+(const rational &other) const;
  rational operator-(const rational &other) const;
  rational operator*(const rational &other) const;
  rational operator/(const rational &other) const;

  // Comparisons
  bool operator==(const rational &other) const;
  bool operator!=(const rational &other) const;
  bool operator<(const rational &other) const;
  bool operator<=(const rational &other) const;
  bool operator>(const rational &other) const;
  bool operator>=(const rational &other) const;

  // Output, e.g. "-42 / 2"
  friend std::ostream& operator<<(std::ostream &os, const rational &r);

  // Parses input and normalizes, e.g. "6 -4" => -3 / 2
  friend std::istream& operator>>(std::istream &is, rational &r);
};

#endif
