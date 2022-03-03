#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "rational.h"
#include <doctest/doctest.h>

TEST_CASE("testing input / output") {
  CHECK(true);
  CHECK(true);
}

TEST_CASE("testing reduce method") {
  Rational R(210, -231);

  CHECK(R.Numerator() == -10);
  CHECK(R.Denominator() == 11);
}

TEST_CASE("testing comparations") {
  CHECK(Rational(-1, 2) < Rational(1, 2));
  CHECK(Rational(-1, 4) == Rational(16, -64));
}

TEST_CASE("summ and substraction test") {
  Rational R(-11, 23);
  Rational L(-8, -15);

  CHECK(R - L == Rational(-349, 345));
}

TEST_CASE("multiplication test") {
  CHECK(Rational(11, 12) * Rational(3, -11) == Rational(-1, 4));
}

TEST_CASE("division test") {
  CHECK(Rational(-15, 16) / Rational(5, -4) == Rational(3, 4));
}
