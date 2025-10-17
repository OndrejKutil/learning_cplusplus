#include <iostream>
#include <vector>
#include <algorithm>

struct Stock {
    std::string ticker;
    double price;
    int peRatio;
};

double compareByPrice(const Stock &a, const Stock &b) {
    return a.price < b.price;
}

std::vector<Stock> sortByPrice(std::vector<Stock> &stocks) {
    std::sort(stocks.begin(), stocks.end(), compareByPrice);
    return stocks;
}

void printVector(const std::vector<Stock> &stocks) {
    for (const Stock &stock : stocks) {
        std::cout << "Ticker: " << stock.ticker 
                  << ", Price: " << stock.price 
                  << ", P/E Ratio: " << stock.peRatio << std::endl;
    }
}

int main() {
    std::vector<Stock> portfolio = {
        {"AAPL", 150.0, 28},
        {"MSFT", 250.0, 35},
        {"GOOGL", 2800.0, 30},
        {"AMZN", 3400.0, 60},
        {"TSLA", 700.0, 100}
    };

    std::cout << "Portfolio before sorting:" << std::endl;
    printVector(portfolio);

    portfolio = sortByPrice(portfolio);

    std::cout << "Portfolio after sorting by price:" << std::endl;
    printVector(portfolio);

    return 0;
}