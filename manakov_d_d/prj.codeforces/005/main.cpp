#include <iostream>

int main() {
	int N;
	std::cin >> N;

	if (N % 15 == 0) {
		std::cout << "FizzBuzz\n";
	} else if (N % 5 == 0) {
		std::cout << "Buzz\n";
	} else if (N % 3 == 0) {
		std::cout << "Fizz\n";
	}
}
