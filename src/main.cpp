#include <iostream>

#include "CalendarRenderer.h"
#include "Date.h"

int main() {
    std::string input;
    std::cout << "Podaj datę (DD.MM.YYYY | YYYY-MM-DD MM/DD/YYYY): ";
    std::cin >> input;
    try {
        Date date = Date::parse(input);
        std::cout << "ISO8601: " << date.toISO8601() << std::endl;
        std::cout << date.toLongFormat() << std::endl;
        std::cout << "\n";
        renderCalendar(date, std::cout);
    } catch (const std::exception& err) {
        std::cerr<<err.what() <<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
