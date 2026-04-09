#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;
public:
    CustomException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

double divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return static_cast<double>(numerator) / denominator;
}

int accessArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds.");
    }
    return arr[index];
}

void nestedFunction() {
    throw CustomException("Error in nestedFunction");
}

void outerFunction() {
    try {
        nestedFunction();
    } catch (const CustomException& e) {
        std::cout << "Caught exception in outerFunction: " << e.what() << std::endl;
        throw;
    }
}

int main() {
    std::cout << "Nested Exception Demo \n";
    try {
        outerFunction();
    } catch (const CustomException& e) {
        std::cout << "Caught rethrown exception in main: " << e.what() << "\n\n";
    }

    std::cout << "Division Demo \n";
    int numerator, denominator;
    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        double result = divide(numerator, denominator);
        std::cout << "Result: " << result << '\n';
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    std::cout << "Array Access Demo" << '\n';
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    int* arr = new int[size];
    std::cout << "Filling array with values 0 to " << size - 1 << '\n';
    for (int i = 0; i < size; ++i) {
        arr[i] = i * 10;
    }

    int index;
    std::cout << "Enter index to access: ";
    std::cin >> index;

    try {
        int value = accessArray(arr, size, index);
        std::cout << "Element at index " << index << ": " << value << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    delete[] arr;
    return 0;
}