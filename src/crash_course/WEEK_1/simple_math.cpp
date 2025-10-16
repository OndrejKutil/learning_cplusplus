#include <iostream>
#include <cmath>

int main() {
    int a = 10;
    int b = 3;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;


    std::cout << "a^b = " << pow(a, b) << std::endl; // a^b
    std::cout << "sqrt(a) = " << sqrt(a) << std::endl; // square root of a
    std::cout << "round(4.6) = " << round(4.6) << std::endl; // round to nearest integer
    std::cout << "round(-1.4) = " << round(-1.4) << std::endl; // round to nearest integer

    std::cout << "ceil(4.2) = " << ceil(4.2) << std::endl; // round up

    return 0;
}