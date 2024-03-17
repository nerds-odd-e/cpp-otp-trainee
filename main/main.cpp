#include <iostream>
#include "Birthday.h"
#include "AuthenticationService.h"

int main() {
//    Birthday birthday;
//    std::cout << "is birthday: " << birthday.IsBirthday() << std::endl;
//    std::cout << "Hello, World!" << std::endl;
    ProfileDao profileDao;
    RsaTokenDao rsaTokenDao;
    AuthenticationService authenticationService = AuthenticationService(profileDao, rsaTokenDao);
    std::cout << "is valid: " << authenticationService.isValid("joey", "91000000") << std::endl;
    return 0;
}
