#pragma once

#include <string>
#include <vector>

#include "plot.hpp"
#include "player.hpp"
#include "bunny.hpp"

class Farm {
private:
    int rows;
    int columns;
    int current_day = 1;
    Player *player;
    std::vector<std::vector<Plot*>> plots;

    Bunny *bunny = nullptr;

public:
    Farm(int rows, int columns, Player *player);
    ~Farm();

    int number_of_rows();
    int number_of_columns();
    int day() const;

    std::string get_symbol(int row, int column);
    void plant(int row, int column, Plot *plot);
    void harvest(int row, int column);
    void water(int row, int column);
    void end_day();

    void maybe_spawn_bunny();
    void bunny_eat_if_plant();
    void bunny_check_fear();
    void bunny_move();
};