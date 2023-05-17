#pragma once
#include "Commodity.h"

class Fruit : public Commodity {
public:
    Fruit();
    Fruit(uint64_t _cid, std::string _name, double _price, int _day);
    int getDay() const;
    void setDay(int);
    Commodity* clone();
    std::string getDesc();
    void modify();
private:
    int day; // 保质期，按天计
};