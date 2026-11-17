#include "CalendarRenderer.h"
#include "Date.h"
#include <array>
#include <iomanip>
#include <ostream>
#include <string_view>

namespace {
   constexpr char RED[] = "\x1b[91m";
   constexpr char WHITE[] = "\x1b[97m";
   constexpr char GREY[] = "\x1b[90m";
   constexpr char RESET[] = "\x1b[0m";
   constexpr char SELECTED[] = "\x1b[44m";
   constexpr std::array<std::string_view, 12> MONTH_NAMES = {
      "Styczeń", "Luty", "Marzec",
      "Kwiecień", "Maj", "Czerwiec",
      "Lipiec", "Sierpień", "Wrzesień",
      "Październik", "Listopad", "Grudzień"
  };
}

void renderCalendar(const Date &date, std::ostream &out) {
   const int firstWeekday = (date.weekday() - ((date.day() - 1) % 7) + 7) % 7;
   const int daysInMonth = date.getDaysInMonth();
   const int previousMonthDays = firstWeekday > 0 ? date.firstDayOfPreviousMonth().getDaysInMonth() : 0;

   out
   << MONTH_NAMES[date.month() - 1] << " " << date.year() << "\n"
   << std::setw(2) << "PN" << " "
   << std::setw(2) << "WT" << " "
   << std::setw(2) << "SR" << " "
   << std::setw(2) << "CZ" << " "
   << std::setw(2) << "PT" << " "
   << std::setw(2) << "SB" << " "
   << std::setw(2) << "ND" << "\n";

   out << GREY;
   for (int weekday = 0; weekday < firstWeekday; ++weekday) {
      out << std::setw(2) << previousMonthDays - firstWeekday + weekday + 1<< " ";
   }
   out << RESET;

   int day = 1;
   bool currentMonth = true;

   for (int week = 0; week < 6 && currentMonth; ++week) {
      for (int weekday = (week == 0 ? firstWeekday : 0); weekday < 7; ++weekday) {
         if (day == date.day() && currentMonth) {
            out << SELECTED << WHITE;
         }
         if (weekday >= 5) {
            out << RED;
         }
         if (!currentMonth) {
            out << GREY;
         }

         out << std::setw(2) << day << " ";
         out << RESET;

         ++day;

         if (day > daysInMonth) {
            day = 1;
            currentMonth = false;
         }
      }
      out << "\n";
   }
}
