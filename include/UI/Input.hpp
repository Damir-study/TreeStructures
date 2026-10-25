#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
T get_value() {
    T value;
    while (!(std::cin >> value)) {
        if (std::cin.eof()) throw std::runtime_error("Ввод завершён");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Повторите: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

template <>
std::string get_value<std::string>() {
    std::string value;
    if (!std::getline(std::cin, value)) throw std::runtime_error("Ввод завершён");
    return value;
}

int get_int() { return get_value<int>(); }

#endif // UI_INPUT_HPP
