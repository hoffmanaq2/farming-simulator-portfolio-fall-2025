#pragma once
#include <string>
#include "farm.hpp"

class FarmPrinter {
private:
    Farm *farm;

public:
    FarmPrinter(Farm *farm);
    std::string pp();
};