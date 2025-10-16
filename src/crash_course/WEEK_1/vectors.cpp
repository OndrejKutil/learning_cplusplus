#include <iostream>
#include <vector>

// difference between array and vector
// array has fixed size, vector can grow and shrink dynamically


int main() {
    std::vector<double> temperatures = { 72.5, 75.0, 78.2, 80.1, 79.5 };

    int size = temperatures.size();

    double sum = 0.0;
    for (double temp : temperatures) {
        sum += temp;
    }
    double average = sum / size;

    std::cout << "Average temperature: " << average << std::endl;
    std::cout << "Number of readings: " << size << std::endl;

    temperatures.push_back(81.3); // add new temperature
    std::cout << "New number of readings after adding one: " << temperatures.size() << std::endl;

    temperatures.pop_back(); // remove last temperature
    std::cout << "Number of readings after removing last: " << temperatures.size() << std::endl;

    temperatures[2] = 77.0; // change third temperature
    std::cout << "Third temperature after change: " << temperatures[2] << std::endl;

    // remove nth element
    int n = 1; // remove second element
    temperatures.erase(temperatures.begin() + n);
    std::cout << "Number of readings after removing second: " << temperatures.size() << std::endl;

    temperatures.clear(); // remove all elements
    std::cout << "Number of readings after clearing all: " << temperatures.size() << std::endl;

    return 0;
}