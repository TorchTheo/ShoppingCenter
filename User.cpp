#include "include/User.h"
User::User() {
    orders = std::vector<uint64_t>();
}
uint64_t User::getUid() const {
    return uid;
}
void User::setUid(uint64_t _uid) {
    uid = _uid;
}
std::string User::getUsername() const {
    return username;
}
void User::setUsername(std::string _username) {
    username = _username;
}
std::string User::getPassword() const {
    return password;
}
void User::setPassword(std::string _password) {
    password = _password;
}
bool User::getSex() const {
    return sex;
}
void User::setSex(bool _sex) {
    sex = _sex;
}
std::string User::getContact() const {
    return contact;
}
void User::setContact(std::string _contact) {
    contact = _contact;
}
std::string User::getAddress() const {
    return address;
}
void User::setAddress(std::string _address) {
    address = _address;
}
double User::getBalance() const {
    return balance;
}
void User::setBalance(double _balance) {
    balance = _balance;
}