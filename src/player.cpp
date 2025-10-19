#include "player.hpp"

int Player::row() { return current_row; }
int Player::column() { return current_column; }

void Player::move_up(int min_row) {
    if (current_row > min_row)
        current_row--;
}

void Player::move_down(int max_row) {
    if (current_row < max_row - 1)
        current_row++;
}

void Player::move_left(int min_col) {
    if (current_column > min_col)
        current_column--;
}

void Player::move_right(int max_col) {
    if (current_column < max_col - 1)
        current_column++;
}