#include <iostream>
#include <vector>

struct Date {
    int day;
    int month;
    int year;
};

struct Position {
    std::string ticker;
    double avgPrice;
    double quantity;
};

enum class OrderType {
    BUY,
    SELL
};

struct Order {
    std::string ticker;
    double price;
    double quantity;
    OrderType type;
    Date date;
};

class Portfolio {
    public:
        void addOrder(const Order &order) {
            orders.push_back(order);

            if (order.type == OrderType::BUY) {
                addPosition({order.ticker, order.price, order.quantity});
                return;
            } else if (order.type == OrderType::SELL) {
                removePosition(order.ticker, order.quantity);
                return;
            }

        }

        void printPositions() {
            if (positions.empty()) {
                std::cout << "No positions in portfolio." << std::endl;
                return;
            }
            else {
                std::cout << "Current Portfolio Positions:" << std::endl;
                for (const Position &pos : positions) {
                    std::cout << "Ticker: " << pos.ticker 
                            << ", Avg Price: " << pos.avgPrice 
                            << ", Quantity: " << pos.quantity << std::endl;
                }
                return;
            }
        }

        void printOrders() {
            if (orders.empty()) {
                std::cout << "No orders in portfolio." << std::endl;
                return;
            }
            else {
                std::cout << "Order History:" << std::endl;
                for (const Order &order : orders) {
                    std::cout << "Ticker: " << order.ticker 
                            << ", Price: " << order.price 
                            << ", Quantity: " << order.quantity 
                            << ", Type: " << (order.type == OrderType::BUY ? "BUY" : "SELL")
                            << ", Date: " << order.date.day << "/" << order.date.month << "/" << order.date.year
                            << std::endl;
                }
                return;
            }
        }

        void clearPositions() {
            positions.clear();
            return;
        }

        void clearOrders() {
            orders.clear();
            return;
        }

    private:
        std::vector<Position> positions;
        std::vector<Order> orders;

        void addPosition(const Position &pos) {
            for (Position &existingPos : positions) {
                if (existingPos.ticker == pos.ticker) {
                    existingPos.avgPrice = (existingPos.avgPrice * existingPos.quantity + pos.avgPrice * pos.quantity) / (existingPos.quantity + pos.quantity); // Update average price
                    existingPos.quantity += pos.quantity; // Update quantity
                    return;
                }
            }
            positions.push_back(pos); // Add new position if not found
            return;
        }

        void removePosition(const std::string &ticker, double quantity) {
            for (Position &existingPos : positions) {
                if (existingPos.ticker == ticker) {
                    if (existingPos.quantity < quantity) {
                        std::cout << "Error: Not enough quantity to sell for " << ticker << std::endl;
                        return;
                    }
                    existingPos.quantity -= quantity; // Update quantity
                    return;
                }
            }
            std::cout << "Error: No position found for ticker " << ticker << std::endl;
        }
};

int main() {

    Portfolio myPortfolio;

    myPortfolio.addOrder({"AAPL", 150.0, 10, OrderType::BUY, {1, 1, 2023}});
    myPortfolio.addOrder({"AAPL", 160.0, 10, OrderType::BUY, {2, 1, 2023}});

    myPortfolio.printPositions();

    myPortfolio.addOrder({"AAPL", 155.0, 5, OrderType::SELL, {3, 1, 2023}});

    myPortfolio.printPositions();
    myPortfolio.printOrders();

    return 0;
}