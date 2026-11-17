#ifndef PROJEKT_STUDIA_CALENDARRENDERER_H
#define PROJEKT_STUDIA_CALENDARRENDERER_H
#include <iosfwd>

class Date;

void renderCalendar(const Date& date, std::ostream& out);

#endif //PROJEKT_STUDIA_CALENDARRENDERER_H
