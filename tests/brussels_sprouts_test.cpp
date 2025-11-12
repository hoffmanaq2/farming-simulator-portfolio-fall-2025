#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/brussels_sprouts.hpp"

TEST_CASE("Brussels Sprouts start as seed when planted") {
    BrusselsSprouts sprouts;
    REQUIRE(sprouts.symbol() == "x");
    REQUIRE_FALSE(sprouts.is_mature());
}

TEST_CASE("Brussels Sprouts growth over days without watering") {
    BrusselsSprouts sprouts;

    for (int i = 0; i < 5; ++i) sprouts.end_day(); // 5 days - reach sprout
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    for (int i = 0; i < 10; ++i) sprouts.end_day(); // 15 days overall
    REQUIRE(sprouts.symbol() == "B");
    REQUIRE(sprouts.is_mature());
}

TEST_CASE("Brussels Sprouts mature faster when watered") {
    BrusselsSprouts sprouts;
    sprouts.water();
    sprouts.end_day(); // +2 days
    REQUIRE(sprouts.symbol() == "x");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (4)
    REQUIRE(sprouts.symbol() == "x");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (6)
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (8)
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (10)
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (12)
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.water();
    sprouts.end_day(); // +2 more days (14)
    REQUIRE(sprouts.symbol() == "b");
    REQUIRE_FALSE(sprouts.is_mature());

    sprouts.end_day(); // +1 more day (15)
    REQUIRE(sprouts.symbol() == "B");
    REQUIRE(sprouts.is_mature());
}

TEST_CASE("Brussels Sprouts stay mature after reaching maturity") {
    BrusselsSprouts sprouts;
    for (int i = 0; i < 16; ++i) sprouts.end_day(); // 16 days overall
    REQUIRE(sprouts.symbol() == "B");
    REQUIRE(sprouts.is_mature());
}