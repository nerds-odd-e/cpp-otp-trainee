#include "Logger.h"
#include <iostream>

void Logger::log(std::string message) {
    std::cout << message << std::endl;
}

Logger::~Logger() {
}
