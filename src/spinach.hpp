#pragma once

#include <string>
#include "plot.hpp"

class Spinach : public Plot {
private:
    int days_planted = 0;
    bool watered_today = false;
    static const int days_to_sprout = 2;
    static const int days_after_sprout_to_mature = 3;
public:
    std::string symbol() override;
    void end_day() override;
    bool is_mature() const override;
    void water() override;
};