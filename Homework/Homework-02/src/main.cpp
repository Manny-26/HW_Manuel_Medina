#include <iostream>
#include <string>

int main() {
    std::string country;
    std::cout << "Where do you live? ";
    std::getline(std::cin, country);
    std::cout << "I've heard great things about" << country << ", like that its mid! I'd like to go sometime!\n";

    return 0;
}