#include "include/Computer.h"
#include "include/GlobalInfo.h"
#include <iostream>

Computer::Computer() {}
Computer::Computer(uint64_t _cid, std::string _name, double _price, std::string _cpu, std::string _mem, std::string _disk, std::string _graphic) : 
    Commodity(_cid, _name, _price) {
    cpu = _cpu;
    mem = _mem;
    disk = _disk;
    graphic = _graphic;
}
Commodity* Computer::clone() {
    GlobalInfo * g = GlobalInfo::getInstance();
    Commodity* c = new Computer(g->cid_cnt++, getName(), getPrice(), cpu, mem, disk, graphic);
    return c;
}
std::string Computer::getCpu() const {
    return cpu;
}
void Computer::setCpu(std::string _cpu) {
    cpu = _cpu;
}
std::string Computer::getMem() const {
    return mem;
}
void Computer::setMem(std::string _mem) {
    mem = _mem;
}
std::string Computer::getDisk() const {
    return disk;
}
void Computer::setDisk(std::string _disk) {
    disk = _disk;
}
std::string Computer::getGraphic() const {
    return graphic;
}
void Computer::setGraphic(std::string _graphic) {
    graphic = _graphic;
}
std::string Computer::getDesc() {
    return std::string("CPU: ") + cpu + std::string(" 内存: ") + mem + std::string(" 硬盘: ") + disk + std::string(" 显卡: ") + graphic;
}
void Computer::modify() {
    std::cout << "请输入你要修改的项目，1.CPU 2.内存 3.硬盘 4.显卡：";
    int option;
    std::cin >> option;
    std::string _cpu = cpu, _mem = mem, _disk = disk, _graphic = graphic;
    switch (option) {
        case 1:
            std::cout << "请输入修改后的CPU规格：";
            std::cin >> _cpu;
            getchar();
            break;
        case 2:
            std::cout << "请输入修改后的内存规格：";
            std::cin >> _mem;
            getchar();
            break;
        case 3:
            std::cout << "请输入修改后的硬盘规格：";
            std::cin >> _disk;
            getchar();
            break;
        case 4:
            std::cout << "请输入修改后的显卡规格：";
            std::cin >> _graphic;
            getchar();
            break;
    }
    std::cout << "\n请确认修改信息无误\n";
    std::cout << "****************************************\n";
    std::cout << "商品ID：" << getCid() << std::endl;
    std::cout << "商品名称：" << getName() << std::endl;
    printf("商品价格：%.1lf\n", getPrice());
    std::cout << "商品描述：" << std::string("CPU: ") + _cpu + std::string(" 内存: ") + _mem + std::string(" 硬盘: ") + _disk + std::string(" 显卡: ") + _graphic << std::endl;
    std::cout << "****************************************\n";
    char opt;
    std::cout << "确认修改?(y/n)\n";
    std::cin >> opt;
    getchar();
    if (opt == 'y') {
        cpu = _cpu;
        mem = _mem;
        disk = _disk;
        graphic = _graphic;
        std::cout << "修改成功！\n";
        std::cout << "*********************************************************************************************" << std::endl;
    }
    else {
        std::cout << "取消修改\n";
    }
}