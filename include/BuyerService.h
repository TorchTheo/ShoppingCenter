#pragma once
#include "UserService.h"
#include "Buyer.h"

class BuyerService : public UserService {
public:
    void modifyInfo();
    void findPassword();
    void pushOrder(Order* order);
    void recharge();
    void showOrders();
    void showMenu();
    User* regi();
    void setUser(User*);
    void query();
    void searchCommodity();
    void action();
    void purchase();
private:
    Buyer* user;
};