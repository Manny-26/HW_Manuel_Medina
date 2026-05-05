#include <iostream>
#include <map>
#include <vector>

int main() {
    std::map<int, std::vector<int>> numbers1 = {
        {1, {1}}, {2, {2}}, {3, {3}}, {4, {4}}, {5, {5}},
        {6, {6}}, {7, {7}}, {8, {8}}, {9, {9}}
    };

    std::map<int, std::vector<int>> numbers2 = {
        {1, {10}}, {2, {20}}, {3, {30}}, {4, {40}}, {5, {50}},
        {6, {60}}, {7, {70}}, {8, {80}}, {9, {90}}
    };


    for (const auto& pair : numbers2) {
        for (const int val : pair.second) {
            numbers1[pair.first].push_back(val);
        }
    }

    std::cout << "Interlaced map (numbers1): ";
    for (const auto& pair : numbers1) {
        std::cout << pair.first << ": ";
        for (int i = 0; i < pair.second.size(); i++) {
            std::cout << pair.second[i];
            if (i < pair.second.size() - 1) std::cout << ", ";
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    return 0;
}