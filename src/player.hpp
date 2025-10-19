#pragma once

class Player {
private:
    int current_row = 0;
    int current_column = 0;

public:
    int row();
    int column();
    void move_up(int min_row = 0);
    void move_down(int max_row);
    void move_left(int min_col = 0);
    void move_right(int max_col);
};