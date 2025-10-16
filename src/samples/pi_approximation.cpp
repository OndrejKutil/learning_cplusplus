#include <iostream>
#include <cmath>
#include <random>

double calculateDistanceFromOrigin(double x, double y) {
    return sqrt(x * x + y * y);
}

double random_double(double lowerBound, double upperBound) {
    
    // Validate input bounds
    if (lowerBound >= upperBound) {
        throw std::invalid_argument("lowerBound must be less than upperBound");
    }
    else if (lowerBound == upperBound) {
        return lowerBound; // or upperBound, since they are equal
    }
            
    // random_device is a source of non-deterministic seed values provided by the OS.
    // Declaring it 'static' makes it a single persistent object shared across all
    // calls to this function, avoiding re-initialization overhead each time.
    // basically created on first call of random_double() and reused after that
    // each call (rd()) produces a new random seed.
    // static std::random_device rd;
    // static thread_local std::mt19937 eng(rd());

    // mt19937 is a fast pseudo-random number generator (Mersenne Twister).
    // We seed it once from random_device. Marking it 'static' ensures the engine keeps its internal state between calls, producing a continuous random sequence rather than restarting on every invocation.
    // thread_local ensures that each thread has its own instance of the engine, preventing data races in multi-threaded scenarios.
    static thread_local std::mt19937 eng(42); // fixed seed for reproducibility

    // uniform_real_distribution generates floating-point values uniformly in the half-open interval [lowerBound, upperBound).
    // We use std::nextafter to ensure upperBound is included in the range of possible outputs.
    // nextafter works by returning the next representable value for the type (double here) in the direction of the second argument (infinity here).
    // This way we effectively have [lowerBound, upperBound] as our range.
    std::uniform_real_distribution<double> distr(lowerBound, std::nextafter(upperBound, std::numeric_limits<double>::infinity()));

    // Draw one random sample from the distribution using the engine.
    return distr(eng);
}

int main() {
    int samples = 1'000'000; // number of random samples
    int insideCircle = 0;
    int outsideCircle = 0;

    int lowerBound = 0;
    int upperBound = 1;

    for (int i = 0; i < samples; i++) {

        // Generate a random point (x, y) where both x and y are in the range [0, 1]
        double point[2] = { random_double(lowerBound, upperBound), random_double(lowerBound, upperBound) };

        // Calculate the distance from the origin (0, 0)
        double distance = calculateDistanceFromOrigin(point[0], point[1]);
        
        if (distance <= 1.0) {
            insideCircle++;
        } else {
            outsideCircle++;
        }
    }

    // insideCircle / samples gives us the ratio of points inside the quarter circle to total points in the unit square
    // we are using only quarter of the circle, so we multiply by 4 to get the full circle approximation
    // because area of unit square is 1 and area of unit circle is pi*r^2 = pi*1^2 = pi
    double pi = 4.0 * insideCircle / samples;
    std::cout << "Estimated value of Pi: " << pi << std::endl;

    return 0;
}