#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <sstream>

#include "rational.h"

TEST_CASE("testing input / output") {
  std::stringstream ss;
  ss << "-3 -7";

  CHECK(ss.good());

  Rational R;
  ss >> R;
  CHECK(R == Rational(3, 7));
  ss.clear();

  ss << R;
  std::string output;
  std::getline(ss, output);
  CHECK(output == "3 / 7");
}

TEST_CASE("testing reduce method") {
  Rational R(210, -231);

  CHECK(R.num() == -10);
  CHECK(R.denum() == 11);
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

TEST_CASE("other") {
  Rational r(123);

  CHECK(r == Rational(123, 1));
}