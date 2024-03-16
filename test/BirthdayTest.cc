#include "CppUTest/TestHarness.h"
#include "Birthday.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Birthday) {
    void setup() {
    }

    void teardown() {
        mock().checkExpectations();
        mock().clear();
    }
};

extern "C" {
#include "Today.h"
}

//std::tm* date;
//
//std::tm* GetToday() {
//    return date;
//}
//
//void SetToday(int month, int day) {
//    std::time_t currentTime = std::time(NULL);
//    date = std::localtime(&currentTime);
//    date->tm_mon = month - 1;
//    date->tm_mday = day;
//}

std::tm* GetToday() {
    return (std::tm*)mock().actualCall("GetToday").returnValue().getObjectPointer();
}

void SetToday(int month, int day) {
    std::time_t currentTime = std::time(NULL);
    std::tm* date = std::localtime(&currentTime);
    date->tm_mon = month - 1;
    date->tm_mday = day;
    mock().expectOneCall("GetToday").andReturnValue(date);
}

TEST(Birthday, IsBirthday) {
    SetToday(4, 9);
    Birthday target;

    bool actual = target.IsBirthday();

    CHECK_TRUE(actual);
}

TEST(Birthday, IsNotBirthday) {
    SetToday(4, 8);
    Birthday target;

    bool actual = target.IsBirthday();

    CHECK_FALSE(actual);
}
