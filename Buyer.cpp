#include "include/Buyer.h"
#include <iostream>

Buyer::Buyer(uint64_t _uid, std::string _username, std::string _password, bool _sex, std::string _contact, std::string _address, double _balance) : User() {
    setUid(_uid);
    setUsername(_username);
    setPassword(_password);
    setSex(_sex);
    setContact(_contact);
    setAddress(_address);
    setBalance(_balance);
    type = 0;
}

void Buyer::showInfo() {
    std::cout << "************************************\n";
    std::cout << "用户身份：\t买家" << std::endl;
    std::cout << "用户名：\t" << this->getUsername() << std::endl;
    std::cout << "联系方式：\t" << this->getContact() << std::endl;
    std::cout << "地址：\t\t" << this->getAddress() << std::endl;
    printf("钱包余额：\t%.1lf\n", this->getBalance());
    std::cout << "************************************\n";
}

bool Buyer::login(std::string _username, std::string _password) {
    if (getUsername() != _username || getPassword() != _password)
        return false;
    return true;
}