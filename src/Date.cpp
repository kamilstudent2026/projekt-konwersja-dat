#include "Date.h"

#include <array>
#include <string_view>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
    int parseNumber(const std::string& numstr, const int start, const int end) {
        const int n = static_cast<int>(numstr.length()) - 1;

        if (start < 0 || end < 0 || start > n || end > n || end < start) {
            throw std::out_of_range("Wrong range provided for parseNumber");
        }

        int result = 0;

        for (int i = start; i <= end; ++i) {
            const char ch = numstr[i];
            if (ch < '0' || ch > '9') {
                throw std::invalid_argument("Invalid data in date");
            }
            result = result * 10 + (ch - '0');
        }

        return result;
    }

    bool isLeapYear(const int year) {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }

    int daysInMonth(const int month, const int year) {
        constexpr std::array<int, 12> days = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        if (month == 2 && isLeapYear(year)) {
            return 29;
        }

        return days[month - 1];
    }
}

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {

    if (year < 1 || year > 9999) {
        throw std::invalid_argument("Invalid year");
    }

    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month");
    }

    if (day < 1 || day > daysInMonth(month, year)) {
        throw std::invalid_argument("Invalid day");
    }
}

Date Date::parse(const std::string& datestr) {
    if (datestr.length() != 10) {
        throw std::invalid_argument("Date must be of length = 10");
    }

    int year;
    int month;
    int day;

    if (datestr[2] == '.' && datestr[5] == '.') {
        // DD.MM.YYYY
        day = parseNumber(datestr, 0, 1);
        month = parseNumber(datestr, 3, 4);
        year = parseNumber(datestr, 6, 9);

    } else if (datestr[4] == '-' && datestr[7] == '-') {
        // YYYY-MM-DD
        year = parseNumber(datestr, 0, 3);
        month = parseNumber(datestr, 5, 6);
        day = parseNumber(datestr, 8, 9);

    } else if (datestr[2] == '/' && datestr[5] == '/') {
        // MM/DD/YYYY
        month = parseNumber(datestr, 0, 1);
        day = parseNumber(datestr, 3, 4);
        year = parseNumber(datestr, 6, 9);

    } else {
        throw std::invalid_argument("Invalid date format or delimiter");
    }

    if (year < 1) {
        throw std::invalid_argument("Wrong year given, year must be 0001 or bigger");
    }

    if (month == 0 || month > 12) {
        throw std::invalid_argument("Month must be in range 1-12, wrong value given");
    }

    if (day == 0 || day > daysInMonth(month, year)) {
        throw std::invalid_argument("Invalid date, wrong day given");
    }

    return Date{year, month, day};
}

std::string Date::toISO8601() const {
    std::ostringstream out;

    out<<std::setfill('0')
        <<std::setw(4)<<year_<<"-"
        <<std::setw(2)<<month_<<"-"
        <<std::setw(2)<<day_;

    return out.str();
}

std::string Date::toLongFormat() const {
    constexpr std::array<std::string_view, 12> monthsLabels = {
        "stycznia", "lutego", "marca",
        "kwietnia", "maja", "czerwca",
        "lipca", "sierpnia", "września",
        "października", "listopada", "grudnia"
    };
    std::ostringstream out;
    out <<day_<<" "<<monthsLabels[month_ - 1]<<" "<<year_;
    return out.str();
}

Date Date::firstDayOfPreviousMonth() const {
    if (month_ == 1) {
        return Date{year_ - 1, 12, 1};
    }

    return Date{year_, month_ - 1, 1};
}

int Date::getDaysInMonth() const {
    return daysInMonth(month_, year_);
}

int Date::day() const noexcept {
    return day_;
}

int Date::month() const noexcept {
    return month_;
}

int Date::year() const noexcept {
    return year_;
}

int Date::weekday() const noexcept {
    const int completedYears = year_ - 1;
    int const leapYears = completedYears/4 - completedYears/100 + completedYears/400;
    int daysElapsed = 365*completedYears + leapYears; //dni od 01.01.0001 do początku roku

    for (int m = 1; m < month_; ++m) {
        daysElapsed += daysInMonth(m, year_);
    }

    daysElapsed += day_ - 1;

    return daysElapsed % 7;
}
