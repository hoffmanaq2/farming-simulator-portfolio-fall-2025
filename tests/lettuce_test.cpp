#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/lettuce.hpp"

TEST_CASE("Lettuce starts as seed when planted") {
    Lettuce lettuce;
    REQUIRE(lettuce.symbol() == "x");
    REQUIRE_FALSE(lettuce.is_mature());
}

TEST_CASE("Lettuce growth over days without watering") {
    Lettuce lettuce;

    lettuce.end_day(); // day 1
    REQUIRE(lettuce.symbol() == "x"); // still seed

    lettuce.end_day(); // day 2
    REQUIRE(lettuce.symbol() == "o"); // sprout
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.end_day(); // day 3
    REQUIRE(lettuce.symbol() == "o"); // sprout
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.end_day(); // day 4
    REQUIRE(lettuce.symbol() == "O"); // mature
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Lettuce matures faster when watered") {
    Lettuce lettuce;
    lettuce.water();
    lettuce.end_day(); // counts as 2 days
    REQUIRE(lettuce.symbol() == "o"); // sprout

    lettuce.water(); // +2 days
    lettuce.end_day(); // mature
    REQUIRE(lettuce.symbol() == "O");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Multiple watering in same day does not stack") {
    Lettuce lettuce;
    lettuce.water();
    lettuce.water();
    lettuce.end_day(); // +2 days from watering
    lettuce.end_day(); // +1 day
    lettuce.end_day(); // +1 day (4 overall)
    REQUIRE(lettuce.symbol() == "O");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Lettuce stays mature after reaching maturity") {
    Lettuce lettuce;
    lettuce.end_day();
    lettuce.end_day();
    lettuce.end_day();
    lettuce.end_day();
    lettuce.end_day(); // Extra day
    REQUIRE(lettuce.symbol() == "O");
    REQUIRE(lettuce.is_mature());
}