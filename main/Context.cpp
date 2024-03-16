#include "Context.h"
#include <map>

std::map<std::string, std::string> Context::profiles;

Context::Context() {
    profiles.insert(std::make_pair("joey", "91"));
    profiles.insert(std::make_pair("mei", "99"));
}

std::string Context::getPassword(const std::string userName) {
    return profiles[userName];
}
