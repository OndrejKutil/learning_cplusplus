#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Task {
    std::string title;
    bool done = false;
};

void printMenu() {
    std::cout << "\n=== TODO MENU ===\n";
    std::cout << "1. Add task\n";
    std::cout << "2. List tasks\n";
    std::cout << "3. Save tasks\n";
    std::cout << "4. Load tasks\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    std::vector<Task> tasks;

    // TODO: Implement menu loop and actions
    // Suggested file name: tasks.txt

    return 0;
}
