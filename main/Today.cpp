#include "Today.h"

std::tm* GetToday() {
    std::time_t t = std::time(0);
    return std::localtime(&t);
}
