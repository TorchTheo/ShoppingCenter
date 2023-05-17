#pragma once

#include <unistd.h>
#include <string>

class Order {
public:
    Order(uint64_t _oid, uint64_t _cid, uint64_t _sid, uint64_t _bid, std::string _date);
    uint64_t getBuyerID() const;
    uint64_t getCid() const;
    std::string getDate() const;
    uint64_t getSellerID() const;
    uint64_t getOid() const;
    double getTransaction() const;
private:
    uint64_t cid;
    uint64_t oid;
    uint64_t seller_id;
    uint64_t buyer_id;
    std::string date;
    double transaction;
};