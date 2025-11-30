#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/bunny.hpp"

TEST_CASE("Bunny initializes with correct row and column") {
    Bunny b(2, 3);
    REQUIRE(b.row() == 2);
    REQUIRE(b.column() == 3);
}

TEST_CASE("Bunny setters correctly update position") {
    Bunny b(0, 0);
    b.set_row(4);
    b.set_column(5);
    REQUIRE(b.row() == 4);
    REQUIRE(b.column() == 5);
}

TEST_CASE("Bunny scared flag is false by default") {
    Bunny b(1, 1);
    REQUIRE(b.is_scared() == false);
}

TEST_CASE("Bunny becomes scared when scare() is called") {
    Bunny b(1, 1);
    b.scare();
    REQUIRE(b.is_scared() == true);
}

TEST_CASE("Bunny calms down after calm_down()") {
    Bunny b(1, 1);
    b.scare();
    REQUIRE(b.is_scared() == true);
    b.calm_down();
    REQUIRE(b.is_scared() == false);
}