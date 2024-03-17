#include "CppUTest/TestHarness.h"
#include "AuthenticationService.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(AuthenticationService) {
    void setup() {
        mock().ignoreOtherCalls();
    }

    void teardown() {
        mock().checkExpectations();
        mock().clear();
    }
};

//class ProfileDaoStub : public ProfileDao {
//public:
//    std::string getPassword(std::string userName) {
//        return "91";
//    }
//};
//
//class RsaTokenDaoStub : public RsaTokenDao {
//public:
//    std::string getRandom(std::string userName) {
//        return "000000";
//    }
//};
//
//class LoggerMock : public Logger {
//public:
//    void log(std::string message) {
//        logMessage = message;
//    }
//
//    std::string logMessage;
//};

class ProfileDaoStub : public ProfileDao {
public:
    std::string getPassword(std::string userName) {
        return mock().actualCall("getPassword").returnStringValueOrDefault("91");
    }

};

class RsaTokenDaoStub : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) {
        return mock().actualCall("getRandom").returnStringValueOrDefault("000000");
    }

};

class LoggerMock : public Logger {
public:
    void log(std::string message) {
        mock().actualCall("log").withParameter("message", message.c_str());
    }

};

TEST(AuthenticationService, IsValid) {
    ProfileDaoStub profileDaoStub;
    RsaTokenDaoStub rsaTokenDaoStub;
    LoggerMock loggerMock;
    AuthenticationService target = AuthenticationService(profileDaoStub, rsaTokenDaoStub, loggerMock);

    bool actual = target.isValid("joey", "91000000");

    CHECK_TRUE(actual);
}

TEST(AuthenticationService, IsInvalid) {
    ProfileDaoStub profileDaoStub;
    RsaTokenDaoStub rsaTokenDaoStub;
    LoggerMock loggerMock;
    AuthenticationService target = AuthenticationService(profileDaoStub, rsaTokenDaoStub, loggerMock);

    bool actual = target.isValid("joey", "91000001");

    CHECK_FALSE(actual);
}

TEST(AuthenticationService, IsInvalidWithLogger) {
    ProfileDaoStub profileDaoStub;
    RsaTokenDaoStub rsaTokenDaoStub;
    LoggerMock loggerMock;
    AuthenticationService target = AuthenticationService(profileDaoStub, rsaTokenDaoStub, loggerMock);

    mock().expectOneCall("log").withParameter("message", "account: joey login failed");

    target.isValid("joey", "91000001");

//    STRCMP_EQUAL("account: joey login failed", loggerMock.logMessage.c_str());
}
