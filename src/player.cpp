#include "player.hpp"

int Player::row() {
    return current_row;
}

int Player::column() {
    return current_column;
}

void Player::move_right() {
    current_column += 1;
}

void Player::move_down() {
    current_row += 1;
}