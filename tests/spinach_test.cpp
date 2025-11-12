#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/spinach.hpp"

TEST_CASE("Spinach starts as seed when planted") {
    Spinach spinach;
    REQUIRE(spinach.symbol() == "x");
    REQUIRE_FALSE(spinach.is_mature());
}

TEST_CASE("Spinach growth over days without watering & stays mature after maturity") {
    Spinach spinach;

    spinach.end_day(); // day 1
    REQUIRE(spinach.symbol() == "x");

    spinach.end_day(); // day 2
    REQUIRE(spinach.symbol() == "s");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // day 3
    REQUIRE(spinach.symbol() == "s");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // day 4
    REQUIRE(spinach.symbol() == "s");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // day 5
    REQUIRE(spinach.symbol() == "S");
    REQUIRE(spinach.is_mature());

    spinach.end_day(); // Extra day
    REQUIRE(spinach.symbol() == "S");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Spinach matures faster when watered") {
    Spinach spinach;
    spinach.water();
    spinach.end_day(); // +2 days
    REQUIRE(spinach.symbol() == "s");
    spinach.end_day(); // +1 more day
    spinach.end_day(); // +1 more day
    spinach.end_day(); // +1 more day
    REQUIRE(spinach.symbol() == "S");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Multiple watering in same day does not stack") {
    Spinach spinach;
    spinach.water(); // +2 days
    spinach.water(); // +0 days
    spinach.end_day();
    spinach.end_day(); // +1 days
    spinach.end_day(); // +1 days
    spinach.end_day(); // +1 days

    REQUIRE(spinach.symbol() == "S");
    REQUIRE(spinach.is_mature());
}