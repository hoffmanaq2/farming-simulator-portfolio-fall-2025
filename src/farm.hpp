#pragma once

#include <string>
#include <vector>

#include "plot.hpp"
#include "player.hpp"

class Farm {
private:
    int rows;
    int columns;
    Player *player;
    std::vector<std::vector<Plot *>> plots;

public:
    Farm(int rows, int columns, Player *player);
    int number_of_rows();
    int number_of_columns();
    std::string get_symbol(int row, int column);
    void plant(int row, int column, Plot *plot);
};