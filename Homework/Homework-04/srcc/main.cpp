#include <iostream>
#include <iomanip>
#include <string>
#include <array>

constexpr std::array<const char*, 12> MONTHS{
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

//constexpr std::array<int,12> DAYS{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year) {
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

int days_in_month(int month, int year) {
    switch (month) {
        case 0:
            return 31;
        case 1:
            return is_leap_year(year) ? 29 : 28;
        case 2:
            return 31;
        case 3:
            return 30;
        case 4:
            return 31;
        case 5:
            return 30;
        case 6:
            return 31;
        case 7:
            return 31;
        case 8:
            return 30;
        case 9:
            return 31;
        case 10:
            return 30;
        case 11:
            return 31;
        default:
            return 0;
    }
}

int year_start(int year) {
    int shift{year - 1};
    int leap_years{year / 4};
    leap_years -= year / 100;
    leap_years += year / 400;
    return ((shift + leap_years) % 7);
}

int main() {
    int year;

    std::cout << "Enter a year from the common era from 1900 or later: ";
    std::cin >> year;

    while (year < 1) {
        std::cout << "Invalid Entry, Try Again: ";
        std::cin >> year;
    }

    std::cout << "\nCalendar for " << year << '\n';

    int current_day = year_start(year);

    for (std::size_t i = 0; i < 11; ++i) {
        std::cout << "--" << MONTHS[i] << ' ' << year << "--\n";
        std::cout << "  Sun Mon Tue Wed Thu Fri Sat\n";

        for (int space = 0; space < current_day; ++space) {
            std::cout << "    ";
        }
        int days = days_in_month(i, year);
        for (int day = 1; day <= days; ++day) {
            std::cout << std::setw(4) << day;
            current_day++;
            if (current_day == 7) {
                std::cout << '\n';
                current_day = 0;
            }
        }
        if (current_day != 0) {
            std::cout << '\n';
        }

        std::cout << '\n';
    }
    return 0;
}