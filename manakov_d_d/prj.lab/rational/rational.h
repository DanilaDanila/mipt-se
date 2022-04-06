#ifndef RATIONAL_H
#define RATIONAL_H

#include <iosfwd>

class Rational {
public:
  Rational();
  Rational(const Rational &) = default;
  Rational(Rational &&) = default;
  Rational(const int num, const int denum = 1);

  Rational &operator=(const Rational &) = default;
  Rational &operator=(Rational &&) = default;

  int num() const;
  int denum() const;

  const Rational &operator+() const;
  const Rational operator-() const;

  Rational &operator+=(const Rational &rhs);
  Rational &operator-=(const Rational &rhs);
  Rational &operator*=(const Rational &rhs);
  Rational &operator/=(const Rational &rhs);

  bool operator==(const Rational &rhs) const;
  bool operator!=(const Rational &rhs) const;
  bool operator<(const Rational &rhs) const;
  bool operator<=(const Rational &rhs) const;
  bool operator>(const Rational &rhs) const;
  bool operator>=(const Rational &rhs) const;

  std::istream &read_from(std::istream &in);
  std::ostream &write_to(std::ostream &out) const;

private:
  /*       numerator
   * R = -------------
   *      denominator
   */
  int numerator = 0;
  int denominator = 1;

  void reduce();
};

std::istream &operator>>(std::istream &in, Rational &r);
std::ostream &operator<<(std::ostream &out, const Rational &r);

const Rational operator+(const Rational &lhs, const Rational &rhs);
const Rational operator-(const Rational &lhs, const Rational &rhs);
const Rational operator*(const Rational &lhs, const Rational &rhs);
const Rational operator/(const Rational &lhs, const Rational &rhs);

#endif // RATIONAL_H
