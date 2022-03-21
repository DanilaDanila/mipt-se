#include "rational.h"

#include <stdexcept>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define _SIGN(a) (((a) >= 0) ? 1 : -1)  // incorrect but very usefull
#define ABS(a) (((a) > 0) ? (a) : -(a))

Rational::Rational(const int numerator, const int denominator)
    : numerator(_SIGN(numerator) * _SIGN(denominator) * ABS(numerator)),
      denominator(ABS(denominator)) {
  // check correct input
  if (denominator == 0) {
    throw std::invalid_argument("denominator = 0");
  }

  reduce();
}

const Rational Rational::operator+() const { return *this; }

const Rational Rational::operator-() const {
  return Rational(-numerator, denominator);
}

Rational &Rational::operator+=(const Rational &other) {
  numerator = numerator * other.denominator + other.numerator * denominator;
  denominator *= other.denominator;

  reduce();

  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  *this += -other;
  reduce();

  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  numerator *= other.numerator;
  denominator *= other.denominator;
  reduce();

  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  if (other.num() == 0) {
    throw std::overflow_error("Divide by zero exception");
  }

  numerator *= other.denominator;
  denominator *= other.numerator;
  reduce();

  return *this;
}

Rational::operator std::string() const {
  return std::to_string(numerator) + "/" + std::to_string(denominator);
}

const int &Rational::num() const { return numerator; }

const int &Rational::denum() const { return denominator; }

void Rational::reduce() {
  if (numerator == 0) {
    denominator = 1;
    return;
  }

  for (int i = 1; i <= MIN(ABS(numerator), ABS(denominator)); ++i)
    if (numerator % i == 0 && denominator % i == 0) {
      numerator /= i;
      denominator /= i;
    }

  if (numerator <= 0 && denominator < 0) {
    numerator *= -1;
    denominator *= -1;
  }
}

std::istream &Rational::read_from(std::istream &in) {
  int num;
  int denom;
  char slash;
  in >> num >> std::noskipws >> slash >> denom >> std::skipws;

  if (in.fail()) {
    return in;
  }

  if (slash != '/' || denom <= 0) {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  *this = Rational(num, denom);
  return in;
}

std::ostream &Rational::write_to(std::ostream &out) const {
  out << std::string(*this);

  return out;
}

std::istream &operator>>(std::istream &in, Rational &rational) {
  return rational.read_from(in);
}

std::ostream &operator<<(std::ostream &out, const Rational &rational) {
  return rational.write_to(out);
}

bool operator<(const Rational &first, const Rational &second) {
  return first.num() * second.denum() < second.num() * first.denum();
}

bool operator>(const Rational &first, const Rational &second) {
  return second < first;
}

bool operator<=(const Rational &first, const Rational &second) {
  return !(first > second);
}

bool operator>=(const Rational &first, const Rational &second) {
  return !(first < second);
}

bool operator==(const Rational &first, const Rational &second) {
  return first <= second && first >= second;
}

bool operator!=(const Rational &first, const Rational &second) {
  return first < second || first > second;
}

const Rational operator+(const Rational &first, const Rational &second) {
  return Rational(first) += second;
}

const Rational operator-(const Rational &first, const Rational &second) {
  return Rational(first) -= second;
}

const Rational operator*(const Rational &first, const Rational &second) {
  return Rational(first) *= second;
}

const Rational operator/(const Rational &first, const Rational &second) {
  return Rational(first) /= second;
}
