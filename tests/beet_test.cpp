#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/beet.hpp"

TEST_CASE("Beet starts as seed when planted") {
    Beet beet;
    REQUIRE(beet.symbol() == "x");
    REQUIRE_FALSE(beet.is_mature());
}

TEST_CASE("Beet growth over days without watering & stays mature after maturity") {
    Beet beet;

    beet.end_day(); // Day 1
    REQUIRE(beet.symbol() == "x");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // Day 2 - becomes "u"
    REQUIRE(beet.symbol() == "u");
    REQUIRE_FALSE(beet.is_mature());

    for (int i = 0; i < 5; ++i) beet.end_day(); //+5 days (7 days overall)
    REQUIRE(beet.symbol() == "U");
    REQUIRE(beet.is_mature());

    beet.end_day(); // Extra day
    REQUIRE(beet.symbol() == "U");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Beet matures faster when watered") {
    Beet beet;
    beet.water();
    beet.end_day(); // +2 days
    REQUIRE(beet.symbol() == "u");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // +1 day (3 total)
    REQUIRE(beet.symbol() == "u");
    REQUIRE_FALSE(beet.is_mature());

    beet.water();
    beet.end_day(); // +2 more days (5 total)
    REQUIRE(beet.symbol() == "u");
    REQUIRE_FALSE(beet.is_mature());

    beet.water();
    beet.end_day(); // +2 more days (7 total)
    REQUIRE(beet.symbol() == "U");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Beet stays mature after reaching maturity") {
    Beet beet;
    for (int i = 0; i < 8; ++i) beet.end_day(); // 8 days overall
    REQUIRE(beet.symbol() == "U");
    REQUIRE(beet.is_mature());
}