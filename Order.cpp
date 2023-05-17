#include "include/Order.h"

Order::Order(uint64_t _oid, uint64_t _cid, uint64_t _sid, uint64_t _bid, std::string _date)
    : oid(_oid), cid(_cid), seller_id(_sid), buyer_id(_bid), date(_date) {

}

uint64_t Order::getSellerID() const
{
    return this->seller_id;
}

uint64_t Order::getBuyerID() const
{
    return this->buyer_id;
}

uint64_t Order::getOid() const
{
    return this->oid;
}

std::string Order::getDate() const
{
    return this->date;
}

uint64_t Order::getCid() const
{
    return this->cid;
}

double Order::getTransaction() const {
    return transaction;
}
