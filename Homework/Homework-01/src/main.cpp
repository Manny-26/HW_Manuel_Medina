#include <bitset>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

// checks if input is an int
bool is_integer(const std::string& input) {
    for (char character : input) {
        if (!std::isdigit(character) && !std::isspace(character) &&
            character != '-' && character != '+')
            return false;
    }
    return true;
}
// checks if input was a float
bool is_float(const std::string& input) {
    for (char character : input) {
        if (!std::isdigit(character) && !std::isspace(character) &&
            character != '-' && character != '+' && character != '.')
            return false;
    }
    return true;
}

int main() {
    std::string input;
    std::cout << "Input any real number or any alphabetical characters to "
                 "convert them to binary: ";
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "No input provided exiting program.";
        return 1;
    }

    if (is_integer(input)) {
        long long int num{std::stoll(input)};
        std::cout << "Your whole number integer as binary: "
                  << std::bitset<sizeof(long long int) * 8>{
                         static_cast<unsigned long long int>(num)};
    } else if (is_float(input)) {
        double num{std::stod(input)};
        double* ptr_num{&num};
        unsigned long long shoved;
        unsigned long long* ptr_shoved{&shoved};
        std::memcpy(ptr_shoved, ptr_num, sizeof(unsigned long long));
        std::cout << "Your floating point number integer as binary: "
                  << std::bitset<sizeof(long long int) * 8>{shoved};
    } else {
        std::cout << "Your ascii string in binary: ";
        for (char character : input) {
            std::cout << std::bitset<sizeof(char) *
                                     8>{static_cast<unsigned long long>(
                             character)}
                      << ' ';
        }
    }

    return 0;
}