#include <iostream>

#include "src/player.hpp"
#include "src/farm.hpp"
#include "src/farm_printer.hpp"
#include "src/carrot.hpp"
//#include "src/ansi_clear.hpp"

int main() {
    Player player;
    Farm farm(5, 6, &player);
    FarmPrinter printer(&farm);
    bool game_in_progress = true;
    std::string player_input;

    while(game_in_progress) {
        std::cout << printer.pp() << std::endl;
        std::cout << "Enter command: ";
        std::cin >> player_input;

        if(player_input == "q") {
            game_in_progress = false;
        } else if (player_input == "w") {
            player.move_up();
        } else if (player_input == "s") {
            player.move_down(farm.number_of_rows());
        } else if (player_input == "a") {
            player.move_left();
        } else if (player_input == "d") {
            player.move_right(farm.number_of_columns());
        } else if(player_input == "c") {
            Carrot *carrot = new Carrot();
            farm.plant(player.row(), player.column(), carrot);
        } else if (player_input == "h") {
            farm.harvest(player.row(), player.column());
        } else if (player_input == "e") {
            farm.end_day();
        }
    }
}