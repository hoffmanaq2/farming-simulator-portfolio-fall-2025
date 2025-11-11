#include "lettuce.hpp"

std::string Lettuce::symbol() {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    if (days_planted == 0) {
        return "x";
    } else if (days_planted < days_to_sprout) {
        return "x";
    } else if (days_planted < total_to_mature) {
        return "o"; // lettuce seedling (lowercase)
    } else {
        return "O"; // mature lettuce (uppercase)
    }
}

void Lettuce::end_day() {
    int advance = 1;
    if (watered_today) {
        advance = 2;
    }
    days_planted += advance;
    watered_today = false;
}

bool Lettuce::is_mature() const {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    return days_planted >= total_to_mature;
}

void Lettuce::water() {
    watered_today = true;
}