#pragma once
#include "UserService.h"
#include "Seller.h"
#include "Commodity.h"
#include <unistd.h>

class SellerService : public UserService {
public:
    void modifyInfo();
    void findPassword();
    void pushOrder(Order* order);
    void recharge();
    void showOrders();
    Commodity* putUpCommodity();
    void showCommodities();
    void showMenu();
    User* regi();
    void setUser(User*);
    void modifyCommodity();
    void putDownCommodity();
    void action();
private:
    Seller *user;
};