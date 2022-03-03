#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
    public:
        Rational();

        ~Rational();

        Rational(const int numerator, const int denominator=1);

        Rational(const Rational&);

        Rational(Rational &&other);

        Rational &operator=(const Rational&);

        Rational &operator=(Rational &&other);

        const Rational operator+() const;

        const Rational operator-() const;

        Rational &operator+=(const Rational&);

        Rational &operator-=(const Rational&);

        Rational &operator*=(const Rational&);

        Rational &operator/=(const Rational&);

        const int &Numerator() const;

        const int &Denominator() const;

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


// comparisons
bool operator<(const Rational &first, const Rational &second);

bool operator>(const Rational &first, const Rational &second);

bool operator<=(const Rational &first, const Rational &second);

bool operator>=(const Rational &first, const Rational &second);

bool operator==(const Rational &first, const Rational &second);

bool operator!=(const Rational &first, const Rational &second);


// binary arithmetic operators
const Rational operator+(const Rational &first, const Rational &second);

const Rational operator-(const Rational &first, const Rational &second);

const Rational operator*(const Rational &first, const Rational &second);

const Rational operator/(const Rational &first, const Rational &second);


#endif // RATIONAL_H
