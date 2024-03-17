#include "CppUTest/TestHarness.h"
#include "AuthenticationService.h"

TEST_GROUP(AuthenticationService) {
};

class ProfileDaoStub : public ProfileDao {
public:
    std::string getPassword(std::string userName) {
        return "91";
    }
};

class RsaTokenDaoStub : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) {
        return "000000";
    }
};

class LoggerMock : public Logger {
public:
    void log(std::string message) {
        logMessage = message;
    }

    std::string logMessage;
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

    target.isValid("joey", "91000001");

    STRCMP_EQUAL("account: joey login failed", loggerMock.logMessage.c_str());
}
