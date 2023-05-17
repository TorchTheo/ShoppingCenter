#include "include/GlobalInfo.h"
#include <iostream>
#include <iomanip>
GlobalInfo *GlobalInfo::instance = nullptr;

void GlobalInfo::ppause() {
    std::cout << "按回车键继续...\n";
    fgetc(stdin);
}

bool GlobalInfo::checkUsername(std::string username) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto user : g->users) {
        if (user->getUsername() == username)
            return false;
    }
    return true;
}

bool GlobalInfo::checkRegisterContact(std::string contact) {
    for (int i = 0; i < contact.size(); i++)
        if (!(contact[i] >= '0' && contact[i] <= '9')) {
            std::cout << "\033[31m!!!联系方式仅能包含数字!!!\n\033[0m";
            return false;
        }
    return true;
}

bool GlobalInfo::checkRegisterPassword(std::string password) {
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

bool GlobalInfo::checkRegisterUsername(std::string username) {
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

User* GlobalInfo::getUser(uint64_t uid) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto user : g->users) {
        if (user->getUid() == uid)
            return user;
    }
    return nullptr;
}

Commodity* GlobalInfo::getCommodity(uint64_t cid) {
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto com : g->commodities) {
        if (com->getCid() == cid)
            return com;
    }
    return nullptr;
}

Order* GlobalInfo::getOrder(uint64_t oid) {
    auto g = GlobalInfo::getInstance();
    for (auto order : g->orders) {
        if (order->getOid() == oid)
            return order;
    }
    return nullptr;
}

GlobalInfo::GlobalInfo() {
    users = std::vector<User*>();
    commodities = std::vector<Commodity*>();
    orders = std::vector<Order*>();
    cu_map = std::unordered_map<uint64_t, uint64_t>();
    uid_cnt = cid_cnt = oid_cnt = 1;
}

GlobalInfo* GlobalInfo::getInstance() {
    if (instance == nullptr)
        instance = new GlobalInfo();
    return instance;
}

void GlobalInfo::showAllCommodities() const {
    std::cout << "所有商品清单如下" << std::endl;
    std::cout << "**********************************************************************************\n";
    std::cout << "ID\t\t名称\t\t\t价格\t上架时间\t商品状态\n";
    for (auto c : commodities) {
        if (c->getStatus() == Commodity::XJ || c->getStatus() == Commodity::SC)
            continue;
        std::cout << c->getCid() << "\t\t" << std::left << std::setw(24) << c->getName() << "\t";
        printf("%.1lf\t", c->getPrice());
        std::cout << c->getDate() << "\t";
        std::cout << "销售中\n";
    }
    std::cout << "**********************************************************************************\n";
}