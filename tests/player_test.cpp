#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"

TEST_CASE("Player starts at 0,0") {
    Player p;
    REQUIRE(p.row() == 0);
    REQUIRE(p.column() == 0);
}

TEST_CASE("Player movement within farm boundaries") {
    Player p;

    SECTION("Move right within boundary") {
        p.move_right(5);
        REQUIRE(p.column() == 1);
    }

    SECTION("Move down within boundary") {
        p.move_down(5);
        REQUIRE(p.row() == 1);
    }

    SECTION("Cannot move left past boundary") {
        p.move_left();
        REQUIRE(p.column() == 0);
    }

    SECTION("Cannot move up past boundary") {
        p.move_up();
        REQUIRE(p.row() == 0);
    }

    SECTION("Stops at max boundaries") {
        for (int i = 0; i < 10; i++) p.move_right(3);
        for (int i = 0; i < 10; i++) p.move_down(3);
        REQUIRE(p.row() == 2);
        REQUIRE(p.column() == 2);
    }
}