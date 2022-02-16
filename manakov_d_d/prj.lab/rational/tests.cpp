#include <iostream>
#include <cassert>
#include "rational.cpp"

#define TEST(testname, funcname) { \
    std::cerr << testname << "\n"; \
    assert(funcname()); \
    std::cerr << "OK\n\n"; \
};

bool IOTest() {
    Rational R;
    std::cin >> R;

    std::cout << R << " == '333 / 721'" <<"\n";
    return true;
}

bool ReduceTest() {
    Rational R(210, -231);

    return R.Numerator() == -10 && R.Denominator() == 11;
}

bool CmpTest() {
    return  Rational(-1, 2) < Rational(1, 2) &&
            Rational(-1, 4) == Rational(16, -64);
}

bool SumSubTest() {
    Rational R(-11, 23);
    Rational L(-8, -15);

    return R - L == Rational(-349, 345);
}

bool MulTest() {
    return Rational(11, 12) * Rational(3, -11) == Rational(-1, 4);
}

bool DivTest() {
    return Rational(-15, 16) / Rational(5, -4) == Rational(3, 4);
}

void RunTests() {
    TEST("IO Test", IOTest);
    TEST("Reduce Test", ReduceTest);
    TEST("Comparation Test", CmpTest);
    TEST("Summ and Substraction Test", SumSubTest);
    TEST("Multiplication Test", MulTest);
}

int main() {
    RunTests();
    return 0;
}