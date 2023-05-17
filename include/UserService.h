#pragma once

#include <string>
#include "User.h"
#include "Order.h"

class UserService {
public:
    virtual void modifyInfo() = 0;
    virtual void findPassword() = 0;
    virtual void pushOrder(Order* order) = 0;
    virtual void recharge() = 0;
    virtual void showOrders() = 0;
    virtual void showMenu() = 0;
    virtual User* regi() = 0;
    virtual void setUser(User*) = 0;
    virtual void action() = 0;
private:
    User *user;
};