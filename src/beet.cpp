#include "beet.hpp"

std::string Beet::symbol() {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    if (days_planted == 0) {
        return "x";
    } else if (days_planted < days_to_sprout) {
        return "x";
    } else if (days_planted < total_to_mature) {
        return "u"; // beet seedling (lowercase) -> user wanted 'u'->'U'
    } else {
        return "U"; // mature beet (uppercase)
    }
}

void Beet::end_day() {
    int advance = 1;
    if (watered_today) {
        advance = 2;
    }
    days_planted += advance;
    watered_today = false;
}

bool Beet::is_mature() const {
    int total_to_mature = days_to_sprout + days_after_sprout_to_mature;
    return days_planted >= total_to_mature;
}

void Beet::water() {
    watered_today = true;
}
