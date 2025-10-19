#pragma once

#include <string>

#include "plot.hpp"

class Carrot : public Plot {
public:
    std::string symbol() override;
};