#pragma once
#include "UserService.h"

class Controller {
public:
    static Controller * getInstance();
    void showMenu();
    void exitSys();
    void Login();
    void buyerRegister();
    void sellerRegister();
    void reset();
    void findPass();
private:
    Controller();
    static Controller * instance;
    UserService* service;
};