#pragma once
#include <vector>
#include <unordered_map>
#include "User.h"
#include "Commodity.h"
#include "Order.h"

class GlobalInfo {
public:
    GlobalInfo();
    std::vector<User*> users;
    std::vector<Commodity*> commodities;
    std::vector<Order*> orders;
    std::unordered_map<uint64_t, uint64_t> cu_map;
    uint64_t uid_cnt;
    uint64_t cid_cnt;
    uint64_t oid_cnt;
    static GlobalInfo * getInstance();
    static void ppause();
    static bool checkUsername(std::string username);
    static bool checkRegisterContact(std::string contact);
    static bool checkRegisterPassword(std::string password);
    static bool checkRegisterUsername(std::string username);
    static User* getUser(uint64_t uid);
    static Commodity* getCommodity(uint64_t cid);
    static Order* getOrder(uint64_t oid);
    void showAllCommodities() const;
private:
    static GlobalInfo * instance;
};