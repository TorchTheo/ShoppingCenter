#pragma once
#include "User.h"
class Buyer : public User {
public:
    Buyer(uint64_t _uid, std::string _username, std::string _password, bool _sex, std::string _contact, std::string _address, double _balance);
    void showInfo();
    bool login(std::string username, std::string password);
};