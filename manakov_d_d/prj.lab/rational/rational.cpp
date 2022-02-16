#ifndef RATIONAL_CPP
#define RATIONAL_CPP

#include <iostream>
#include <stdexcept>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define _SIGN(a) (((a) >= 0) ? 1 : -1)  // incorrect but very usefull
#define ABS(a) (((a) > 0) ? (a) : -(a))

class Rational {
	public:
		Rational() = default;

		~Rational() = default;

		Rational(const int numerator, const int denominator=1):
			numerator(_SIGN(numerator) * _SIGN(denominator) * ABS(numerator)),
			denominator(ABS(denominator))
		{
			// check correct input
			if (denominator == 0) {
				throw std::invalid_argument("denominator = 0");
			}

			// reduce
			reduce();
		}

		Rational(const Rational &other) = default;
		// Rational(const Rational &&other) = default;

		Rational &operator=(const Rational &other) = default;
		// Rational &operator=(const Rational &&other) = default;

		const Rational operator+() const { return *this; }
		const Rational operator-() const {
			return Rational(-numerator, denominator);
		}

		Rational &operator+=(const Rational &other) {
			numerator = numerator * other.denominator + other.numerator * denominator;
			denominator *= other.denominator;

			reduce();

			return *this;
		}

		Rational &operator-=(const Rational &other) {
			*this += -other;
			reduce();

			return *this;
		}

		Rational &operator*=(const Rational &other) {
			numerator *= other.numerator;
			denominator *= other.denominator;
			reduce();

			return *this;
		}

		Rational &operator/=(const Rational &other) {
			if (other.Numerator() == 0) {
				throw std::overflow_error("Divide by zero exception");
			}

			numerator *= other.denominator;
			denominator *= other.numerator;
			reduce();

			return *this;
		}

		const int &Numerator() const {
			return numerator;
		}

		const int &Denominator() const {
			return denominator;
		}

	private:
		/*       numerator
		 * R = -------------
		 *      denominator
		 */
		int numerator = 0;
		int denominator = 1;

		void reduce() {
			for (int i = 1; i * i < MIN(ABS(numerator), ABS(denominator)); ++i)
				if (numerator % i == 0 && denominator % i == 0) {
					numerator /= i;
					denominator /= i;
				}
		}
};


std::ostream &operator<<(std::ostream &out, const Rational &rational) {
	out << rational.Numerator() << " / " << rational.Denominator();
	return out;
}

std::istream &operator>>(std::istream &in, Rational &rational) {
	int numerator;
	int denominator;
	in >> numerator >> denominator;

	rational = Rational(numerator, denominator);
	return in;
}

bool operator<(const Rational &first, const Rational &second) {
	return  first.Numerator() * second.Denominator() 
			< 
			second.Numerator() * first.Denominator();
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

#endif  // RATIONAL_CPP
