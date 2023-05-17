#include "include/Commodity.h"
#include "include/GlobalInfo.h"
#include <iomanip>
#include <unistd.h>

Commodity::Commodity() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string _date = std::to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? std::to_string(1 + ltm->tm_mon) : "0" + std::to_string(1 + ltm->tm_mon)) + "-" + ((ltm->tm_mday) >= 10 ? std::to_string(ltm->tm_mday) : "0" + std::to_string(ltm->tm_mday));
    date = _date;
    status = ZS;
}

Commodity::Commodity(uint64_t _cid, std::string _name, double _price) : cid(_cid), name(_name), price(_price) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string _date = std::to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? std::to_string(1 + ltm->tm_mon) : "0" + std::to_string(1 + ltm->tm_mon)) + "-" + ((ltm->tm_mday) >= 10 ? std::to_string(ltm->tm_mday) : "0" + std::to_string(ltm->tm_mday));
    date = _date;
    status = ZS;
}

uint64_t Commodity::getCid() const {
    return cid;
}
void Commodity::setCid(uint64_t _cid) {
    cid = _cid;
}
std::string Commodity::getName() const {
    return name;
}
void Commodity::setName(std::string _name) {
    name = _name;
}
std::string Commodity::getDate() const {
    return date;
}
void Commodity::setDate(std::string _date) {
    date = _date;
}
double Commodity::getPrice() const {
    return price;
}
void Commodity::setPrice(double _price) {
    price = _price;
}
Commodity::STATS Commodity::getStatus() {
    return status;
}
void Commodity::setStatus(STATS _status) {
    status = _status;
}