#include "spinach.hpp"

std::string Spinach::symbol() {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    if (days_planted == 0) {
        return "x";
    } else if (days_planted < days_to_sprout) {
        return "x";
    } else if (days_planted < total_to_mature) {
        return "s"; // spinach seedling (lowercase)
    } else {
        return "S"; // mature spinach (uppercase)
    }
}

void Spinach::end_day() {
    int advance = 1;
    if (watered_today) {
        advance = 2;
    }
    days_planted += advance;
    watered_today = false;
}

bool Spinach::is_mature() const {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    return days_planted >= total_to_mature;
}

void Spinach::water() {
    watered_today = true;
}