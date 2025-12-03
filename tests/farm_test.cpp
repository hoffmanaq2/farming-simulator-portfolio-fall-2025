#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/carrot.hpp"
#include "../src/lettuce.hpp"
#include "../src/spinach.hpp"
#include "../src/beet.hpp"
#include "../src/brussels_sprouts.hpp"
#include "../src/soil.hpp"


// BASIC FARM SETUP TEST
TEST_CASE("Farm initializes correctly with soil plots") {
    Player player;
    Farm farm(3, 4, &player, false);

    REQUIRE(farm.number_of_rows() == 3);
    REQUIRE(farm.number_of_columns() == 4);
    REQUIRE(farm.day() == 1);

    // All plots should be soil initially
    REQUIRE(farm.get_symbol(0, 0) == "@"); // Player start
    REQUIRE(farm.get_symbol(0, 1) == ".");
    REQUIRE(farm.get_symbol(1, 0) == ".");
}


// GENERAL FUNCTIONALITY TESTS
TEST_CASE("Day progression increments and grows a plant (carrot)") {
    Player player;
    Farm farm(2, 2, &player, false);

    farm.plant(0, 1, new Carrot());
    REQUIRE(farm.get_symbol(0, 1) == "x");

    farm.end_day();
    REQUIRE(farm.day() == 2);
    REQUIRE(farm.get_symbol(0, 1) == "v");

    farm.end_day();
    REQUIRE(farm.day() == 3);
    REQUIRE(farm.get_symbol(0, 1) == "V");
}

// PLANT-SPECIFIC TESTS
TEST_CASE("Planting and harvesting carrots") {
    Player player;
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new Carrot());
    REQUIRE(farm.get_symbol(0, 0) == "@"); // player overlays carrot
    farm.end_day();
    farm.end_day();

    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "V"); // mature carrot visible

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

TEST_CASE("Planting and harvesting lettuce") {
    Player player;
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new Lettuce());
    farm.end_day();
    farm.end_day();
    farm.end_day();
    farm.end_day(); // should now be mature

    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "O");

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

TEST_CASE("Planting and harvesting spinach") {
    Player player;
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new Spinach());
    for (int i = 0; i < 5; ++i) farm.end_day(); // reach maturity

    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "S");

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

TEST_CASE("Planting and harvesting beet") {
    Player player;
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new Beet());
    for (int i = 0; i < 7; ++i) farm.end_day();

    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "U");

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

TEST_CASE("Planting and harvesting brussels sprouts") {
    Player player;
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new BrusselsSprouts());
    for (int i = 0; i < 15; ++i) farm.end_day();

    player.move_right(farm.number_of_columns());
    REQUIRE(farm.get_symbol(0, 0) == "B");

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == ".");
}

// WATERING BEHAVIOR TEST
TEST_CASE("Watering accelerates plant growth") {
    Player player;
    Farm farm(2, 2, &player, false);
    Lettuce *lettuce = new Lettuce();

    farm.plant(0, 0, lettuce);
    REQUIRE(farm.get_symbol(0, 0) == "@");

    farm.water(0,0);
    farm.end_day(); // counts as +2 days
    farm.end_day();
    farm.end_day(); // progress to maturity
    REQUIRE(lettuce->is_mature() == true);
}

// ALL PLANTS
TEST_CASE("End day updates all plots consistently") {
    Player player;
    // use 3x3 farm so there is at least one empty cell we can move the player to
    Farm farm(3, 3, &player, false);

    farm.plant(0, 0, new Carrot());
    farm.plant(0, 1, new Lettuce());
    farm.plant(1, 0, new Spinach());
    farm.plant(1, 1, new Beet());
    farm.plant(1, 2, new BrusselsSprouts());

    for (int i = 0; i < 15; ++i)
        farm.end_day();

    // Move player to an empty cell (2,2) so it does not overlay any planted plots.
    player.move_down(farm.number_of_rows()); // from 0->1
    player.move_down(farm.number_of_rows()); // from 1->2
    player.move_right(farm.number_of_columns()); // from 0->1
    player.move_right(farm.number_of_columns()); // from 1->2

    REQUIRE(farm.get_symbol(0, 0) == "V");
    REQUIRE(farm.get_symbol(0, 1) == "O");
    REQUIRE(farm.get_symbol(1, 0) == "S");
    REQUIRE(farm.get_symbol(1, 1) == "U");
    REQUIRE(farm.get_symbol(1, 2) == "B");
}

// BUNNY FEATURE TESTS
// TEST_CASE("Bunny eats a crop when it lands on it") {
//     Player player;
//     Farm farm(3, 3, &player, true); // bunnies enabled
//
//     // Force spawn bunny manually
//     farm.maybe_spawn_bunny();
//     REQUIRE(farm.day() == 1);
//
//     // Move bunny to a known location (center)
//     REQUIRE(farm.day() == 1);
//     REQUIRE(farm.day() == 1);
//
//     // Manually place bunny at (1,1)
//     farm.maybe_spawn_bunny();
//     farm.bunny = new Bunny(1, 1);
//
//     // Plant carrot where bunny is
//     farm.plant(1, 1, new Carrot());
//     REQUIRE(farm.get_symbol(1, 1) == "R"); // bunny overlays plant
//
//     farm.end_day(); // bunny should eat plant
//     REQUIRE(farm.get_symbol(1, 1) == "R"); // bunny still there
//     player.move_right(farm.number_of_columns());
//     player.move_down(farm.number_of_rows());
//     REQUIRE(farm.get_symbol(1, 1) == "."); // soil left behind after eating
// }
//
//
// TEST_CASE("Bunny becomes scared when player stands next to it") {
//     Player player;
//     Farm farm(3, 3, &player, true);
//
//     // Place bunny manually at (1,1)
//     farm.bunny = new Bunny(1, 1);
//
//     // Player moves next to bunny (1,0)
//     player.move_down(farm.number_of_rows());
//
//     farm.end_day(); // triggers fear logic
//
//     REQUIRE(farm.bunny->is_scared() == true);
// }
//
//
// TEST_CASE("Scared bunny runs away from player") {
//     Player player;
//     Farm farm(5, 5, &player, true);
//
//     // Place bunny at center and player next to it
//     farm.bunny = new Bunny(2, 2);
//     player.move_down(farm.number_of_rows()); // player (1,0) → (2,0)
//
//     // Trigger fear on end_day
//     farm.end_day();
//     REQUIRE(farm.bunny->is_scared() == false); // should calm after running
//
//     // After running, bunny should NOT still be near player
//     int br = farm.bunny->row();
//     int bc = farm.bunny->column();
//     REQUIRE_FALSE( (br == 2 && bc == 1) || (br == 2 && bc == 3) || (br == 1 && bc == 2) || (br == 3 && bc == 2) );
// }
//
//
// TEST_CASE("Bunny disappears when running off the map") {
//     Player player;
//     Farm farm(3, 3, &player, true);
//
//     // Place bunny near border
//     farm.bunny = new Bunny(0, 0);
//
//     // Player stands next to bunny so it panics and runs off the map
//     player.move_down(farm.number_of_rows()); // player moves to (1,0)
//     farm.end_day(); // scared bunny moves away off grid
//
//     // If bunny left the map, it should be deleted
//     REQUIRE(farm.get_symbol(0, 0) == "@"); // no bunny here anymore
// }