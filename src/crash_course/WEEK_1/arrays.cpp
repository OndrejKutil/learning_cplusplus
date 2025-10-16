#include <iostream>

int main() {
    const int size = 5;
    int numbers[size] = {10, 20, 30, 40, 50};

    std::cout << "Array elements are: ";
    for (int i = 0; i < size; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    numbers[2] = 100; // change the third element

    std::cout << "Array elements after change: ";
    for (int i = 0; i < size; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}