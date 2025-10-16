#include <iostream>

float calculateCummulativeReturn(int years, float annualReturn) {
    float cummulativeReturn = 1.0;
    for (int i = 0; i < years; i++) {
        cummulativeReturn *= (1 + annualReturn / 100);
    }
    return cummulativeReturn - 1;
}

int main() {
    int years;
    float annualReturn;

    std::cout << "Enter the number of years: ";
    std::cin >> years;
    std::cout << "Enter the annual return percentage: ";
    std::cin >> annualReturn;

    float cummulativeReturn = calculateCummulativeReturn(years, annualReturn);
    std::cout << "The cummulative return over " << years << " years is " 
              << cummulativeReturn * 100 << "%" << std::endl;

    return 0;
}