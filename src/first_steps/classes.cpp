#include <iostream>
#include <random>
#include <memory>

int random_int(int lowerBound, int upperBound) {
    
    // Validate input bounds
    if (lowerBound > upperBound) {
        throw std::invalid_argument("lowerBound must be less than or equal to upperBound");
    }
    if (lowerBound == upperBound) {
        return lowerBound;
    }

    static thread_local std::mt19937 eng(42); // fixed seed for reproducibility

    // uniform_int_distribution generates integer values uniformly in the closed interval [lowerBound, upperBound].
    std::uniform_int_distribution<int> distr(lowerBound, upperBound);

    return distr(eng);
};

class Portfolio {
    private:
        std::unique_ptr<double[]> prices_; // smart pointer to manage dynamic array. heap
        int size_;

    public:
        // Constructor - same name as the class (no return type, __init__ in Python)
        // Using member initializer list to initialize unique_ptr and size
        // automatically initializes prices to a unique_ptr managing an array of n doubles, or nullptr if n <= 0. Initializer list is more efficient.
        // size is initialized to n.
        explicit Portfolio(const int& n) : prices_(n > 0 ? std::make_unique<double[]>(n) : nullptr), size_(n) {

            if (n <= 0) {
                throw std::invalid_argument("Portfolio size must be positive");
            }

            for (int i = 0; i < this->size_; i++) {
                this->prices_[i] = random_int(100, 500);
            }
        } 

        // Copy constructor - same name as the class (no return type), performs deep copy, argument is a reference to another object of the same class
        Portfolio(const Portfolio& other) {
            this->size_ = other.size_;
            this->prices_ = std::make_unique<double[]>(this->size_);

            for (int i = 0; i < this->size_; i++) {
                this->prices_[i] = other.prices_[i];
            }

            std::cout << "Portfolio copied" << std::endl;
        }

        // Destructor - same name as the class with ~ prefix (no return type, __del__ in Python)
        ~Portfolio() = default; // default destructor is sufficient with unique_ptr


        // --- APIs ---

        void print() const {
            for (int i = 0; i < this->size_; i++) {
                std::cout << "Position " << i << ": $" << this->prices_[i] << std::endl;
            }
        }

        int getSize() const {
            return this->size_;
        }

        double getAveragePrice() const {
            double sum = 0.0;

            for (int i = 0; i < this->size_; i++) {
                sum += this->prices_[i];
            }
            
            return sum / this->size_;
        }

        void setPriceAt(int index, double price) {
            if (index < 0 || index >= this->size_) {
                throw std::out_of_range("Index out of range");
            }
            this->prices_[index] = price;
        }

};

int main() {

    std::cout << "Start of program" << std::endl;

    Portfolio myPortfolio(5);
    Portfolio copiedPortfolio = myPortfolio; // invokes copy constructor

    myPortfolio.setPriceAt(0, 999.99);

    std::cout << "Original Portfolio:" << std::endl;
    myPortfolio.print();

    std::cout << "Copied Portfolio:" << std::endl;
    copiedPortfolio.print();

    std::cout << "End of program" << std::endl;

    return 0;
}


