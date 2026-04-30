#include <iostream>
#include <algorithm>
#include <array>

void findMatches(const std::array<int, 5>& arr1, const std::array<int, 4>& arr2) {
    std::cout << "\nMatching numbers: ";
    bool found = false;

    for (const int a : arr1) {
        for (const int b : arr2) {
            if (a == b) {
                std::cout << a << " ";
                found = true;
                break;
            }
        }
    }

    if (!found)
        std::cout << "None";

    std::cout << "\n";
}

int main() {
    std::array<int, 5> data  {1, 3, 6, 7, 9};
    std::array<int, 4> data1 {5, 3, 3, 11};

    std::cout << "Before swap:\n";
    std::cout << "data:  "; for (int n : data)  std::cout << n << " ";
    std::cout << "\ndata1: "; for (int n : data1) std::cout << n << " ";

    size_t swapCount = std::min(data.size(), data1.size());
    for (size_t i{0}; i < swapCount; ++i) {
        std::swap(data[i], data1[i]);
    }

    std::cout << "\n\nAfter swap:\n";
    std::cout << "data:  "; for (int n : data)  std::cout << n << " ";
    std::cout << "\ndata1: "; for (int n : data1) std::cout << n << " ";

    std::cout << "\n\n=== Part 2: Matches ===";
    findMatches(data, data1);

    return 0;
}