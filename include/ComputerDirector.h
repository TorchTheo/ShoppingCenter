#pragma once

#include "ComputerBuilder.h"

class ComputerDirector {
private:
    ComputerBuilder *builder;
public:
    ComputerDirector(ComputerBuilder *_builder);
    Computer* construct();
};