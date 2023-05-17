#pragma once
#include "User.h"
#include "Inventory.h"
class Seller : public User {
public:
    Seller(uint64_t _uid, std::string _username, std::string _password, bool _sex, std::string _contact, std::string _address, double _balance);
    Inventory *inventory;
    void showInfo();
    bool login(std::string username, std::string password);
};