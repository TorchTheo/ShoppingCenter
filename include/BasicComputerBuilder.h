#pragma once
#include "ComputerBuilder.h"

class BasicComputerBuilder : public ComputerBuilder {
public:
    void buildCpu();
    void buildMem();
    void buildDisk();
    void buildGraphic();
    void buildBasicInfo();
};