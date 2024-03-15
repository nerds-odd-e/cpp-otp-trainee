#include "CppUTest/TestHarness.h"
#include "../main/AuthenticationService.h"

TEST_GROUP(AuthenticationService) {
};

TEST(AuthenticationService, IsValid) {
    AuthenticationService target;

    bool actual = target.isValid("joey", "91000000");

    CHECK_TRUE(actual);
}
