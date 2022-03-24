#ifndef RATIONAL_H
#define RATIONAL_H

#include <iosfwd>

class Rational {
 public:
  Rational() = default;

  ~Rational() = default;

  Rational(const int numerator);

  Rational(const int numerator, const int denominator);

  Rational(const Rational &) = default;

  Rational(Rational &&) = default;

  Rational &operator=(const Rational &) = default;

  Rational &operator=(Rational &&) = default;

  Rational operator+() const;

  Rational operator-() const;

  Rational &operator+=(const Rational &);

  Rational &operator-=(const Rational &);

  Rational &operator*=(const Rational &);

  Rational &operator/=(const Rational &);

  explicit operator std::string() const;

  int num() const;

  int denum() const;

  std::istream &read_from(std::istream &);

  std::ostream &write_to(std::ostream &) const;

  // comparisons
  bool operator<(const Rational &second) const;

  bool operator>(const Rational &second) const;

  bool operator<=(const Rational &second) const;

  bool operator>=(const Rational &second) const;

  bool operator==(const Rational &second) const;

  bool operator!=(const Rational &second) const;

 private:
  /*       numerator
   * R = -------------
   *      denominator
   */
  int numerator = 0;
  int denominator = 1;

  void reduce();
};

// input / output
std::ostream &operator<<(std::ostream &out, const Rational &rational);

std::istream &operator>>(std::istream &in, Rational &rational);

// binary arithmetic operators
const Rational operator+(const Rational &first, const Rational &second);

const Rational operator-(const Rational &first, const Rational &second);

const Rational operator*(const Rational &first, const Rational &second);

const Rational operator/(const Rational &first, const Rational &second);

#endif  // RATIONAL_H
