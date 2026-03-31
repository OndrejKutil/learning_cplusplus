#include <iostream>

int main() {
    const int secret = 42;
    int guess = 0;
    int attempts = 0;

    std::cout << "Guess the secret number.\n";

    // TODO: Loop until guess is correct
    // TODO: Print hints (too low / too high)
    // TODO: Count attempts and print at the end°

    while (true) {
        std::cout << "Enter your guess: " << std::endl;
        std::cin >> guess;

        if (guess == secret) {
            break;
        } else if (guess < secret) {
            std::cout << "Number too low" << std::endl;
        } else {
            std::cout << "Number too high" << std::endl;
        }

        attempts++;

    }

    std::cout << "Congratulations! You guessed the number in " << attempts << " attempts." << std::endl;


    return 0;
}
