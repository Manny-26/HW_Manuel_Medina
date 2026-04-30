#include <iostream>
#include <vector>

void loop(const std::vector<int>& numbers) {
    for (int num : numbers) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> numbers1{1, 2, 3, 4, 5};
    std::vector<int> numbers2{10, 20, 30, 40, 50};

    std::size_t minSize{std::min(numbers1.size(), numbers2.size())};

    numbers1.resize(numbers1.size() + numbers2.size());

    auto src = numbers1.begin() + minSize;
    auto dst = numbers1.begin() + (numbers1.size() - minSize);
    if (numbers1.size() - numbers2.size() > numbers2.size()) {
        for (auto src = numbers1.begin() + minSize,
            dst = numbers1.begin() + (numbers1.size() - minSize + 1); dst < numbers1.end(); ++src, ++dst) {
            loop(numbers1);
            *dst = *src;
            loop(numbers1);
            std::cout << "-\n";
        }
    }

    if (numbers2.size() > minSize) {
        for (auto src = numbers2.begin() + minSize,
            dst = numbers1.begin() + (numbers1.size() - minSize + 1); dst < numbers1.end(); ++src, ++dst) {
            loop(numbers1);
            *dst = *src;
            loop(numbers1);
            std::cout << "-\n";
            }
    }

    for (int i = static_cast<int>(minSize) - 1; i >= 0; --i) {
        std::cout << i << '\n';
        loop(numbers1);
        numbers1[static_cast<std::size_t>(i) * 2] = numbers1[static_cast<std::size_t>(i)];
        loop(numbers1);
        std::cout << "-\n";
    }

    auto it2 = numbers2.begin();
    for (std::size_t i = 0; i < minSize; ++i, ++it2) {
        numbers1[i * 2 + 1] = *it2;
    }

    std::cout << "Interlaced vector (numbers1): ";
    for (int num : numbers1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}