#pragma once
#include "Commodity.h"

class CommodityFactory {
public:
    enum Type {
        FRUIT,
        COMPUTER,
    };
    static Commodity* getCommodity(Type type);
};