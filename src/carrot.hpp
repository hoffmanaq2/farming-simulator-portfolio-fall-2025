#pragma once

#include <string>

#include "plot.hpp"

class Carrot : public Plot {
private:
    int days_planted = 0; // 0 = just planted (tilled soil)
    bool watered_today = false;
    static const int days_to_sprout = 1;
    static const int days_after_sprout_to_mature = 1; // additional days

public:
    std::string symbol() override;
    void end_day() override;
    bool is_mature() const override;
    void water() override;
};