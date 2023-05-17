#include "include/Fruit.h"
#include "include/GlobalInfo.h"
#include <iostream>

Fruit::Fruit() {}

Fruit::Fruit(uint64_t _cid, std::string _name, double _price, int _day) : Commodity(_cid, _name, _price) {
    day = _day;
}

int Fruit::getDay() const {
    return day;
}

void Fruit::setDay(int _day) {
    day = _day;
}

Commodity* Fruit::clone() {
    GlobalInfo * g = GlobalInfo::getInstance();
    Commodity* c = new Fruit(g->cid_cnt++, getName(), getPrice(), day);
    return c;
}

std::string Fruit::getDesc() {
    std::string str("保质期：");
    return str + std::to_string(day);
}

void Fruit::modify() {
    int _day;
    std::cout << "请输入修改后的保质期（用天数计）：";
    std::cin >> _day;
    getchar();
    if (day <= 0) {
        std::cout << "保质期不能为0或负数\n";
        GlobalInfo::ppause();
        return;
    }
    std::cout << "\n请确认修改信息无误\n";
    std::cout << "****************************************\n";
    std::cout << "商品ID：" << getCid() << std::endl;
    std::cout << "商品名称：" << getName() << std::endl;
    printf("商品价格：%.1lf\n", getPrice());
    std::cout << "商品描述：" << std::string("保质期：") + std::to_string(day) << std::endl;
    std::cout << "****************************************\n";
    char option;
    std::cout << "确认修改?(y/n)\n";
    std::cin >> option;
    getchar();
    if (option == 'y') {
        setDay(_day);
        std::cout << "修改成功！\n";
        std::cout << "*********************************************************************************************" << std::endl;
    }
    else {
        std::cout << "取消修改\n";
    }
}