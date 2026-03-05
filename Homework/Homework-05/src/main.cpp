#include <iostream>
#include <string>
#include <array>

constexpr std::array<char, 10> VOWELS{'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};

bool is_vowel(char vowel) {
    for (char character: VOWELS) {
        if (vowel == character)
            return true;
    }
    return false;
}

int main() {
    std::cout << "Input a message for a vowel count: ";

    std::string usr_message;
    std::getline(std::cin, usr_message);

    int vowel_count = 0;

    for (char vowel: usr_message) {
        if (is_vowel(vowel)) {
            ++vowel_count;
        }
    }

    std::cout << vowel_count;

    return 0;
}
