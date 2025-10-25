#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/carrot.hpp"


TEST_CASE("Farm initializes correctly with soil plots") {
    Player player;
    Farm farm(3, 4, &player);

    REQUIRE(farm.number_of_rows() == 3);
    REQUIRE(farm.number_of_columns() == 4);
    REQUIRE(farm.day() == 1);

    // All plots should be soil initially
    REQUIRE(farm.get_symbol(0, 0) == "@"); // Player start
    REQUIRE(farm.get_symbol(0, 1) == ".");
    REQUIRE(farm.get_symbol(1, 0) == ".");
}

TEST_CASE("Planting and harvesting carrots") {
    Player player;
    Farm farm(3, 3, &player);

    // Plant carrot at player's position
    farm.plant(player.row(), player.column(), new Carrot());
    REQUIRE(farm.get_symbol(0, 0) == "@"); // player symbol overlays
    farm.end_day(); // Grow carrot

    // Move off plot to see carrot symbol
    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "V"); // mature carrot visible

    // Harvest mature carrot
    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

TEST_CASE("End of day increments and matures plants") {
    Player player;
    Farm farm(2, 2, &player);

    farm.plant(0, 1, new Carrot());
    REQUIRE(farm.day() == 1);
    REQUIRE(farm.get_symbol(0, 1) == "v");

    farm.end_day();
    REQUIRE(farm.day() == 2);
    REQUIRE(farm.get_symbol(0, 1) == "V");
}