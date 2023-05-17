#pragma once
#include "Computer.h"

class ComputerBuilder {
protected:
    Computer *computer = new Computer();
public:
    virtual void buildCpu() = 0;
    virtual void buildMem() = 0;
    virtual void buildDisk() = 0;
    virtual void buildGraphic() = 0;
    virtual void buildBasicInfo() = 0;
    Computer* getResult() {
        return computer;
    }
};