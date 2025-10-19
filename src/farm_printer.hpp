#pragma once

class FarmPrinter {
private:
    Farm *farm;

public:
    FarmPrinter(Farm *farm);
    std::string pp();
};