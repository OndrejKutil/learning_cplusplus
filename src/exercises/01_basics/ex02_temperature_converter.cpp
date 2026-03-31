#include <iostream>

int main() {
    double celsius = 0.0;

    std::cout << "Enter temperature in Celsius: ";
    std::cin >> celsius;

    // TODO: Convert Celsius to Fahrenheit using F = C * 9 / 5 + 32
    double fahrenheit = celsius * 9 / 5 + 32;
    // TODO: Print both Celsius and Fahrenheit with labels
    std::cout << "Fahrenheit: " << fahrenheit << "\nCencius: " << celsius << std::endl;
    // TODO (bonus): Convert Fahrenheit back to Celsius
    double new_cels = ( fahrenheit - 32 ) * 5 / 9;
    std::cout << celsius << new_cels << std::endl;

    return 0;
}
