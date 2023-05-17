#include "include/Controller.h"
#include "include/Buyer.h"
#include "include/Seller.h"
#include "include/GlobalInfo.h"
#include "include/BuyerService.h"
#include "include/SellerService.h"
#include <string>
#include <iostream>
#include <cstring>
Controller* Controller::instance = nullptr;

Controller::Controller() {
    service = nullptr;
}

Controller* Controller::getInstance() {
    if (instance == nullptr)
        instance = new Controller();
    return instance;
}

void Controller::showMenu() {
    system("clear");
    std::cout << "======================================================" << std::endl;
    std::cout << "1.登录 2.买家注册 3.卖家注册 4.忘记登录密码 5.退出程序" << std::endl;
    std::cout << "======================================================" << std::endl;
}

void Controller::Login() {
    GlobalInfo * g = GlobalInfo::getInstance();
    std::string username, password;
    std::cout << "请输入用户名: ";
    std::cin >> username;
    getchar();
    std::cout << "请输入密码: ";
    std::cin >> password;
    getchar();
    User *user = nullptr;
    bool flag = false;
    for (int i = 0; i < g->users.size(); i++)
        if (g->users[i]->login(username, password)) {
            user = g->users[i];
            flag = true;
            break;
        }
    if(!flag) {
        std::cout << "用户名或密码错误，请重新选择" << std::endl;
        GlobalInfo::ppause();
        return;
    }
    std::cout << "********** 登陆成功 **********" << std::endl;
    GlobalInfo::ppause();
    if (user->type == 0)
        service = new BuyerService();
    else if (user->type == 1)
        service = new SellerService();
    service->setUser(user);
    service->action();
    reset();
}

void Controller::buyerRegister() {
    reset();
    service = new BuyerService();
    auto user = service->regi();
    service->setUser(user);
    service->action();
    reset();
}

void Controller::sellerRegister() {
    reset();
    service = new SellerService();
    service->setUser(service->regi());
    service->action();
    reset();
}

void Controller::findPass() {
    reset();
    auto g = GlobalInfo::getInstance();
    std::cout << "请输入您要找回密码的账号（UID或者用户名均可）：";
    std::string s;
    std::cin >> s;
    getchar();
    User *user = nullptr;
    for(User* u : g->users) {
        if (s[0] >= '0' && s[0] <= '9') {
            if (u->getUid() == atoi(s.c_str())) {
                user = u;
                break;
            }
        } else {
            if (u->getUsername() == s) {
                user = u;
                break;
            }
        }
    }
    if(!user) {
        std::cout << "!!!帐号不存在!!!\n";
        GlobalInfo::ppause();
        return;
    }
    if (user->type == 0) {
        service = new BuyerService();
        service->setUser(user);
    } else {
        service = new SellerService();
        service->setUser(user);
    }
    service->findPassword();
    reset();
}

void Controller::reset() {
    service = nullptr;
}

void Controller::exitSys() {
    std::cout << "欢迎下次使用" << std::endl;
    exit(0);
}