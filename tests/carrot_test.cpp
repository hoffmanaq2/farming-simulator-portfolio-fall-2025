#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/carrot.hpp"

TEST_CASE ("Carrot returns a v when it is a seedling") {
    Carrot carrot;
    REQUIRE( carrot.symbol() == "v" );
    REQUIRE_FALSE(carrot.is_mature());
}

TEST_CASE ( "Carrot matures after one day") {
    Carrot carrot;
    carrot.end_day();
    REQUIRE(carrot.symbol() == "V");
    REQUIRE(carrot.is_mature());
}

TEST_CASE ( "Carrot does not change after maturity") {
    Carrot carrot;
    carrot.end_day();
    carrot.end_day();
    REQUIRE(carrot.symbol() == "V");
    REQUIRE(carrot.is_mature());
}
