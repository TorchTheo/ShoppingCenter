#include "include/CommodityFactory.h"
#include "include/Fruit.h"
#include "include/Computer.h"
#include "include/BasicComputerBuilder.h"
#include "include/ComputerDirector.h"
#include <string>

Commodity* CommodityFactory::getCommodity(Type type) {
    if (type == FRUIT) {
        Commodity *c = new Fruit();
        return c;
    } else if (type == COMPUTER) {
        BasicComputerBuilder *b = new BasicComputerBuilder();
        ComputerDirector cd(b);
        Commodity *c = cd.construct();
        return c;
    } else {
        return nullptr;
    }
}