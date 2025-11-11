#include <string>

#include "carrot.hpp"

std::string Carrot::symbol() {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    if (days_planted == 0) {
        return "x"; // tilled soil / seed
    } else if (days_planted < days_to_sprout) {
        return "x";
    } else if (days_planted < total_to_mature) {
        return "v"; // seedling (lowercase)
    } else {
        return "V"; // mature (uppercase)
    }
}

void Carrot::end_day() {
    int advance = 1;
    if (watered_today) {
        advance = 2;
    }
    days_planted += advance;
    watered_today = false;
}

bool Carrot::is_mature() const {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    return days_planted >= total_to_mature;
}

void Carrot::water() {
    // watering has effect only once per day
    watered_today = true;
}