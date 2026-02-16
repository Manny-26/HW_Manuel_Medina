#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <array>
#include <iomanip>
constexpr std::size_t MAP_SIZE{21};

constexpr int MAP_LIMIT{MAP_SIZE / 2};

bool is_location_valid(int x, int y) {
    return x <= MAP_LIMIT && x >= -MAP_LIMIT && y <= MAP_LIMIT && y >= -MAP_LIMIT;
}

std::array<std::array<char, MAP_SIZE>, MAP_SIZE> make_map () {
    std::array<std::array<char, MAP_SIZE>, MAP_SIZE> map{};
    for (std::array<char, MAP_SIZE>& row : map) {
        for (char& space : row) {
            space = 'A' + static_cast<char>(std::rand() % 26); // NOLINT(*-msc50-cpp)
        }
    }
    return map;
}

struct UserCoordinate {
    int x{};
    int y{};
};

struct ArrayCoordinate {
    std::size_t x{};
    std::size_t y{};
};

ArrayCoordinate convert_coordinates (UserCoordinate player_location) {
    player_location.x += MAP_LIMIT;
    player_location.y = MAP_LIMIT - player_location.y;
    return {static_cast<std::size_t>(player_location.x), static_cast<std::size_t>(player_location.y)};
}

int main() {

    std::string player_name;

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // NOLINT(*-msc51-cpp)

    std::cout << "Who are you adventurer?\nInput Player Name: ";
    std::cin >> player_name;

    UserCoordinate player_location{};

    std::cout << "Where are you?\nInput Player x and y coordinates (range is \u00B110):";
    std::cin >> player_location.x >> player_location.y;

    while (!is_location_valid(player_location.x, player_location.y)) {
        std::cout << "Invalid location. range is \u00B110. try again: ";
        std::cin >> player_location.x >> player_location.y;
    }

    ArrayCoordinate player_array_location{convert_coordinates(player_location)};

    //std::cout << '(' << player_array_location.x <<", " << player_array_location.y << ")\n";

    std::array<std::array<char, MAP_SIZE>, MAP_SIZE> map{make_map()};

    std::cout << "\33[1;34m   ";



    for (int i{}; i < MAP_SIZE; ++i)
        std::cout << std::setw(2) << i - MAP_LIMIT << " ";
    std::cout << '\n';

    for (std::size_t i{}; i < MAP_SIZE; ++i) {
        std::cout << std::setw(3) << MAP_LIMIT - static_cast<int> (i) << "| ";
        for (std::size_t j{}; j < MAP_SIZE; ++j) {
            if (i == player_array_location.y && j == player_array_location.x)
                std::cout << "\33[1;31m" << map[i][j] << "  \33[1;34m";
            else
                std::cout << map[i][j] << "  ";
        }
        std::cout << '\n';
    }

    std::cout << "\33[1;0m";

    std::cout << player_name << "is located at " << map[player_array_location.y][player_array_location.x] << '.';

    return 0;
}