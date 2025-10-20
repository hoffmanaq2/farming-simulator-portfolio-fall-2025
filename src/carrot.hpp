#pragma once

#include <string>

#include "plot.hpp"

class Carrot : public Plot {
private:
    bool mature = false;

public:
    std::string symbol() override;
    void end_day() override;
    bool is_mature() const;
};