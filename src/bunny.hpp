#pragma once

class Bunny {
private:
    int current_row;
    int current_column;
    bool scared = false;

public:
    Bunny(int row, int column);

    int row();
    int column();

    void set_row(int r);
    void set_column(int c);

    bool is_scared();
    void scare();
    void calm_down();
};