#include <iostream>

int main() {
    int n = 0;

    std::cout << "Print FizzBuzz up to: ";
    std::cin >> n;

    // TODO: Loop from 1 to n
    // TODO: Print Fizz for multiples of 3
    // TODO: Print Buzz for multiples of 5
    // TODO: Print FizzBuzz for multiples of both
    // TODO (bonus): Make divisors/words configurable

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            std::cout << "FizzBuzz" << std::endl;
        } else if (i % 3 == 0) {
            std::cout << "Fizz" << std::endl;
        } else if (i % 5 == 0) {
            std::cout << "Buzz" << std::endl;
        } else {
            std::cout << i << std::endl;
        }
    }

    return 0;
}
