#pragma once

class Player {
private:
    int current_row = 0;
    int current_column = 0;

public:
    int row();
    int column();
    void move_right();
    void move_down();
};