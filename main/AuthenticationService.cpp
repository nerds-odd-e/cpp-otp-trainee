//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    // 根據 account 取得自訂密碼
    std::string passwordFromDao = profileDao.getPassword(userName);

    // 根據 account 取得 RSA token 目前的亂數
    std::string randomCode = rsaToken.getRandom(userName);

    // 驗證傳入的 password 是否等於自訂密碼 + RSA token亂數
    std::string validPassword = passwordFromDao + randomCode;
    bool isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        return false;
    }
}
