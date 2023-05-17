#pragma once
#include <string>
#include <unistd.h>

class Commodity {
public:
    enum STATS {
        ZS, // 在售
        XJ, // 下架
        SC, // 售出
    };
    Commodity();
    Commodity(uint64_t _cid, std::string _name, double _price);
    uint64_t getCid() const;
    void setCid(uint64_t);
    std::string getName() const;
    void setName(std::string);
    std::string getDate() const;
    void setDate(std::string);
    double getPrice() const;
    void setPrice(double);
    STATS getStatus();
    void setStatus(STATS);
    virtual Commodity* clone() = 0;
    virtual std::string getDesc() = 0;
    virtual void modify() = 0;
private:
    uint64_t cid;
    std::string name;
    std::string date;
    double price;
    STATS status;
};