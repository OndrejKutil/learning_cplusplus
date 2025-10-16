#include <iostream>

std::string isOdd(int number) {
    if (number % 2 == 0) {
        return "Even";
    } else {
        return "Odd";
    }
}


/*
int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    std::cout << "The number is " << isOdd(number) << std::endl;

    return 0;
}
*/

std::string dayOfWeek(int day) {
    switch (day) {
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 7: return "Sunday";
        default: return "Invalid day";
    }
}

int main() {
    int day;
    std::cout << "Enter a day number (1-7): ";
    std::cin >> day;

    std::cout << "The day is " << dayOfWeek(day) << std::endl;

    return 0;
}