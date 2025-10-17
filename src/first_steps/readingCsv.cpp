#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readCsv(const std::string& filename) {
    try {
        // Open file, ifstreams destructors closes files automatically if error occurs, but we can also close them manually for better control
        // the file would be closed at the end of this function scope
        std::ifstream file(filename);

        // check if file opened successfully
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return {};
        }

        // initialize line buffer and vector to hold lines
        std::string line;
        std::vector<std::string> lines;

        // read file line by line and store lines in vector
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;

    } catch (std::exception &e) { // catch any exceptions
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return {};
    }
}

// define Ticker struct
struct Ticker {
    std::string symbol;
    double price;
    int volume;
    float peRatio;
};

std::vector<Ticker> parseVectorOfTickers(const std::vector<std::string> &lines) {

    // final vector to hold Ticker structs
    std::vector<Ticker> tickers;

    // skip header line (i = 0)
    for (size_t i = 1; i < lines.size(); ++i) {
        // current line to parse
        const std::string &line = lines[i];
        // temporary Ticker struct to hold parsed data
        Ticker ticker;

        // current position in line
        size_t pos = 0;
        // position of next comma
        size_t commaPos = line.find(',');
        
        try {
            // finds a substring from 0 to first comma
            ticker.symbol = line.substr(pos, commaPos - pos);
            // updates position to character after comma
            pos = commaPos + 1;
            // finds next comma
            commaPos = line.find(',', pos);
            // finds substring from current position to next comma and converts to double (stod - string to double)
            ticker.price = std::stod(line.substr(pos, commaPos - pos));
            pos = commaPos + 1;
            commaPos = line.find(',', pos);
            // (stoi - string to int)
            ticker.volume = std::stoi(line.substr(pos, commaPos - pos));
            pos = commaPos + 1;
            // (stof - string to float)
            ticker.peRatio = std::stof(line.substr(pos));

            tickers.push_back(ticker);

        } catch (const std::exception &e) { // catch any conversion errors
            std::cerr << "Error parsing line " << i + 1 << ": " << e.what() << std::endl;
            continue; // skip to next line
        }
    }

    return tickers;
}


int main() {
    std::vector<Ticker> tickers = parseVectorOfTickers(readCsv("data/tickers.csv"));
    for (const Ticker &ticker : tickers) {
        std::cout << "Symbol: " << ticker.symbol << ", Price: " << ticker.price
                  << ", Volume: " << ticker.volume << ", P/E Ratio: " << ticker.peRatio << std::endl;
    }
    return 0;
}