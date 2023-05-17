#pragma once
#include "Commodity.h"

class Computer : public Commodity {
public:
    Computer();
    Computer(uint64_t _cid, std::string _name, double _price, std::string _cpu, std::string _mem, std::string _disk, std::string _graphic);
    Commodity* clone();
    std::string getCpu() const;
    void setCpu(std::string _cpu);
    std::string getMem() const;
    void setMem(std::string _mem);
    std::string getDisk() const;
    void setDisk(std::string _disk);
    std::string getGraphic() const;
    void setGraphic(std::string _graphic);
    std::string getDesc();
    void modify();
private:
    std::string cpu;
    std::string mem;
    std::string disk;
    std::string graphic;
};