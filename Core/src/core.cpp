#include "core.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>

void processString(std::string &input) {
    std::sort(input.rbegin(), input.rend());
    for (size_t i = 0; i < input.size(); i += 3) {
        input.replace(i, 1, "KV");
    }
}

int sumNumbers(const std::string &input) {
    int sum = 0;
    std::stringstream ss(input);
    std::string temp;
    while (ss >> temp) {
        if (std::all_of(temp.begin(), temp.end(), ::isdigit)) {
            sum += std::stoi(temp);
        }
    }
    return sum;
}

bool checkStringLength(const std::string &input) {
    return input.length() > 2 && input.length() % 32 == 0;
}