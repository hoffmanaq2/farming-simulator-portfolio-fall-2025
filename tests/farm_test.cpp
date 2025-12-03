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
// Farm w/ enable_bunnies = true
Farm* make_farm(Player* p, bool enable_bunnies = true) {
    return new Farm(5, 5, p, enable_bunnies);
}

TEST_CASE("Bunny can be manually placed using set_bunny()") {
    Player p;
    Farm farm(5,5,&p,true);

    Bunny* b = new Bunny(2,3);
    farm.set_bunny(b);

    REQUIRE(farm.get_bunny() != nullptr);
    REQUIRE(farm.get_bunny()->row() == 2);
    REQUIRE(farm.get_bunny()->column() == 3);
}

TEST_CASE("Bunny eats plants at start of day") {
    Player p;
    Farm farm(5,5,&p,true);

    // place carrot at (2,2)
    farm.plant(2,2,new Carrot());
    REQUIRE(farm.get_symbol(2,2) == "x"); //start as seedling "x"

    // place bunny on top
    farm.set_bunny(new Bunny(2,2));

    farm.end_day(); // bunny eats before moving

    REQUIRE(farm.get_symbol(2,2) == "."); // soil
}

TEST_CASE("Bunny gets scared when player moves next to it") {
    Player p;
    Farm farm(5,5,&p,true);

    farm.set_bunny(new Bunny(2,2));

    // player moves to (1,2) which is directly above bunny
    p.move_down(5);  // now at (1,0)
    p.move_right(5); // now at (1,1)
    p.move_right(5); // now at (1,2)

    farm.bunny_check_fear();

    REQUIRE(farm.get_bunny()->is_scared() == true);
}

TEST_CASE("Scared bunny runs 4 squares away from player") {
    Player p;
    Farm farm(10,10,&p,true);

    // player near bunny
    p.move_down(5);     // (1,0)
    p.move_right(5);    // (1,1)
    p.move_right(5);    // (1,2)

    farm.set_bunny(new Bunny(2,2)); // directly below player

    farm.bunny_check_fear(); // becomes scared
    REQUIRE(farm.get_bunny()->is_scared() == true);

    farm.bunny_move(); // bunny should run 4 squares DOWN

    Bunny* b = farm.get_bunny();
    REQUIRE(b != nullptr);
    REQUIRE(b->row() == 6); // 2 + 4
    REQUIRE(b->column() == 2);
}

TEST_CASE("Bunny disappears when it runs off the map") {
    Player p;
    Farm farm(5,5,&p,true);

    // Put bunny near top edge so running away sends it off map
    farm.set_bunny(new Bunny(0,2));

    // place player just above bunny (out of bounds but still triggers logic)
    // simulate fear manually
    farm.get_bunny()->scare();

    farm.bunny_move(); // bunny tries to move up 4 and exits map

    REQUIRE(farm.get_bunny() == nullptr);
}

TEST_CASE("Bunny normal movement moves 1 square within map") {
    Player p;
    Farm farm(5,5,&p,true);

    farm.set_bunny(new Bunny(2,2));

    // Prevent scared movement
    REQUIRE_FALSE(farm.get_bunny()->is_scared());

    farm.bunny_move();

    Bunny* b = farm.get_bunny();
    REQUIRE(b != nullptr);

    // Bunny must only move 1 tile
    int dist = abs(b->row() - 2) + abs(b->column() - 2);
    REQUIRE(dist == 1);
}

TEST_CASE("Bunny never moves onto the player") {
    Player p;
    Farm farm(5,5,&p,true);

    p.move_right(5);  // player → (0,1)

    farm.set_bunny(new Bunny(0,2)); // bunny next to player

    // bunny normal movement may try to move left onto player (0,1)
    for (int i = 0; i < 20; i++)
        farm.bunny_move();

    REQUIRE(!(farm.get_bunny() &&
              farm.get_bunny()->row() == p.row() &&
              farm.get_bunny()->column() == p.column()));
}