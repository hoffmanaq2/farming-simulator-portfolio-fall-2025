#include "soil.hpp"

std::string Soil::symbol() {
    return ".";
}

void Soil::end_day() {
    //no-op
}

void Soil::water() {
    // watering empty soil does nothing
}