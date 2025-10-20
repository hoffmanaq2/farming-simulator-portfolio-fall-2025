#include <string>

#include "carrot.hpp"

std::string Carrot::symbol() {
    return mature ? "V" : "v"; //lower case seedling, uppercase mature
}

void Carrot::end_day() {
    if (!mature) {
        mature = true;
    }
}

bool Carrot::is_mature() const {
    return mature;
}