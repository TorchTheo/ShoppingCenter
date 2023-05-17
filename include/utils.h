#pragma once
#include <iostream>
#include <unistd.h>
#include <string>
#include "GlobalInfo.h"
#include "User.h"
#include "Commodity.h"

void ppause() {
    std::cout << "按回车键继续...\n";
    fgetc(stdin);
}

bool checkUsername(std::string username) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto user : g->users) {
        if (user->getUsername() == username)
            return false;
    }
    return true;
}

bool checkRegisterContact(std::string contact) {
    for (int i = 0; i < contact.size(); i++)
        if (!(contact[i] >= '0' && contact[i] <= '9')) {
            std::cout << "\033[31m!!!联系方式仅能包含数字!!!\n\033[0m";
            return false;
        }
    return true;
}

bool checkRegisterPassword(std::string password) {
    if (password.size() > 20) {
        std::cout << "\033[31m!!!密码多于20位!!!\033[0m" << std::endl;
        return false;
    }
    for (int i = 0; i < password.size(); i++) {
        if (!(password[i] >= '0' && password[i] <= '9') && !(password[i] >= 'a' && password[i] <= 'z')) {
            std::cout << "\033[31m!!!密码只能包含数字和小写字母!!!\n\033[0m";
            return false;
        }
    }
    return true;
}

bool checkRegisterUsername(std::string username) {
    if (username.size() > 10) {
        std::cout << "\033[31m!!!用户名多于10位!!!\n\033[0m";
        return false;
    }
    for (int i = 0; i < username.size(); i++) {
        if (username[i] >= '0' && username[i] <= '9') {
            std::cout << "\033[31m!!!用户名不能含有数字!!!\n\033[0m";
            return false;
        }
    }
    if (!checkUsername(username)) {
        std::cout << "\033[31m!!!用户名已存在!!!\n\033[0m";
        return false;
    }
    return true;
}

User* getUser(uint64_t uid) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto user : g->users) {
        if (user->getUid() == uid)
            return user;
    }
    return nullptr;
}

Commodity* getCommodity(uint64_t cid) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto com : g->commodities) {
        if (com->getCid() == cid)
            return com;
    }
    return nullptr;
}