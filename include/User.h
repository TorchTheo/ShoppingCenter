#pragma once
#include <string>
#include <unistd.h>
#include <vector>

class User {
public:
    User();
    std::vector<uint64_t> orders;
    uint64_t getUid() const;
    void setUid(uint64_t);
    std::string getUsername() const;
    void setUsername(std::string);
    std::string getPassword() const;
    void setPassword(std::string);
    bool getSex() const;
    void setSex(bool);
    std::string getContact() const;
    void setContact(std::string);
    std::string getAddress() const;
    void setAddress(std::string);
    double getBalance() const;
    void setBalance(double);
    virtual void showInfo() = 0;
    virtual bool login(std::string username, std::string password) = 0;
    int type;
private:
    uint64_t uid;
    std::string username;
    std::string password;
    bool sex; // true male, false female
    std::string contact;
    std::string address;
    double balance;
};