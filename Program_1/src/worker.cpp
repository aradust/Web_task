#include "worker.hpp"
#include "core.hpp"
#include <iostream>

void handleInput(std::string &input) {
    
    if (input.length() > 64 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
        std::cerr << "Ошибка: строка должна содержать только цифры и не превышать 64 символа." << std::endl;
        return;
    }
    processString(input);
}