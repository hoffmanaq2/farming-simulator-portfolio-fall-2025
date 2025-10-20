#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"

TEST_CASE( "Player starts in row zero, col zero") {
    Player player;
    REQUIRE ( player.row() == 0 );
    REQUIRE ( player.column() == 0 );
}

TEST_CASE( "it moves the player to the right" ) {
    Player player;
    int max_col = 5;
    player.move_right(max_col);
    REQUIRE( player.row() == 0 );
    REQUIRE( player.column() == 1 );
}

TEST_CASE( " it moves the player to the left, testing bound" ) {
    Player player;
    int min_col = 5;
    player.move_left(min_col);
    REQUIRE( player.row() == 0 );
    REQUIRE( player.column() == 0 );
}

TEST_CASE( " it moves the player up, testing bound" ) {
    Player player;
    int min_row = 5;
    player.move_up(min_row);
    REQUIRE( player.row() == 0 );
    REQUIRE( player.column() == 0 );
}

TEST_CASE( " it moves the player down" ) {
    Player player;
    int max_row = 5;
    player.move_down(max_row);
    REQUIRE( player.row() == 1 );
    REQUIRE( player.column() == 0 );
}