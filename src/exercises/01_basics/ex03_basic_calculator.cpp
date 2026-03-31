#include <iostream>

int main() {
    double a = 0.0;
    double b = 0.0;
    char op = '\0';

    std::cout << "Enter expression (example: 5 * 3): ";
    std::cin >> a >> op >> b;

    // TODO: Handle +, -, *, /
    if (op != '+' || op != '-' || op != '*' || op != '/') {
        throw std::invalid_argument("Enter valid operand");
    }
    // TODO: Guard against division by zero
    if (op == '/' && b == 0) {
        throw std::runtime_error("Division by 0");
    }
    // TODO: Print result or error message
    switch(op) {
        case '+':
            std::cout << a+b << std::endl;
            break;
        case '-':
            std::cout << a-b << std::endl;
            break;
        case '*':
            std::cout << a*b << std::endl;
            break;
        case '/':
            std::cout << a/b << std::endl;
            break;
        default:
            throw std::runtime_error("runtime error");
    }

    return 0;
}
