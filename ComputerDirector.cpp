#include "include/ComputerDirector.h"

ComputerDirector::ComputerDirector(ComputerBuilder *_builder) {
    builder = _builder;
}
Computer* ComputerDirector::construct() {
    builder->buildBasicInfo();
    builder->buildCpu();
    builder->buildMem();
    builder->buildDisk();
    builder->buildGraphic();
    return builder->getResult();
}