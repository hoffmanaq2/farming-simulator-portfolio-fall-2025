#pragma once

#include <string>
#include <vector>

#include "plot.hpp"
#include "player.hpp"

class Farm {
private:
    int rows;
    int columns;
    int current_day = 1;
    Player *player;
    std::vector<std::vector<Plot*>> plots;

public:
    Farm(int rows, int columns, Player *player);

    int number_of_rows();
    int number_of_columns();
    int day() const;

    std::string get_symbol(int row, int column);
    void plant(int row, int column, Plot *plot);
    void harvest(int row, int column);
    void end_day();
};