#include "Birthday.h"

bool Birthday::IsBirthday() {
    std::tm* localTime = GetToday();

    int currentDay = localTime->tm_mday;
    int currentMonth = localTime->tm_mon + 1;
    return currentDay == 9 && currentMonth == 4;
}
