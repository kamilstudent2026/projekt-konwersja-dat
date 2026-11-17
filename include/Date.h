#ifndef PROJEKT_STUDIA_DATE_H
#define PROJEKT_STUDIA_DATE_H
#include <string>


class Date {
private:
    int year_;
    int month_;
    int day_;

    Date(int year, int month, int day);
public:
    static Date parse(const std::string& datestr);

    std::string toISO8601() const;
    std::string toLongFormat() const;

    Date firstDayOfPreviousMonth() const;
    int getDaysInMonth() const;

    int day() const noexcept;
    int month() const noexcept;
    int year() const noexcept;
    int weekday() const noexcept;
};


#endif //PROJEKT_STUDIA_DATE_H
