#include <iostream>

int main() {
    constexpr double pi = 3.14159265358979323846;
    int shape;
    double height;
    double width;
    std::cout <<
            "1. Calculate the area of a square.\n2. Calculate the area of a rectangle.\n3. Calculate the area of a circle.\n4. Calculate the area of a cylinder.\nPlease enter your choice: (1-4) ";
    std::cin >> shape;
    switch (shape) {
        default:
            return 0;
        case 1: {
            std::cout << "Enter height: ";
            std::cin >> height;
            std::cout << "Enter width: ";
            std::cin >> width;
            std::cout << "The area of a square is: " << height * width;
            break;
        }
        case 2: {
            std::cout << "Enter height: ";
            std::cin >> height;
            std::cout << "Enter width: ";
            std::cin >> width;
            std::cout << "The area of a rectangle is: " << height * width;
            break;
        }
        case 3: {
            std::cout << "Enter width: ";
            std::cin >> width;
            double radius = width / 2;
            std::cout << "The area of a circle is: " << pi * radius * radius;
            break;
        }
        case 4: {
            std::cout << "Enter height: ";
            std::cin >> height;
            std::cout << "Enter width: ";
            std::cin >> width;
            double radius = width / 2;
            std::cout << "The area of a cylinder is: " << 2 * pi * radius * (radius + height);
            break;
        }
    }
}
