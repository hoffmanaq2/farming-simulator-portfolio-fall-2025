#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/carrot.hpp"

// Test 1: When first planted, carrot should show as seed ("x")
TEST_CASE("Carrot starts as seed when planted") {
    Carrot carrot;
    REQUIRE(carrot.symbol() == "x");
    REQUIRE_FALSE(carrot.is_mature());
}

// Test 2: Carrot grows each day, becomes seedling "v" after sprouting, then "V" when mature
TEST_CASE("Carrot growth over days without watering") {
    Carrot carrot;

    // Day 0 → just planted
    REQUIRE(carrot.symbol() == "x");
    REQUIRE_FALSE(carrot.is_mature());

    // Day 1 end → still "x" (tilled/seed stage for 1 day)
    carrot.end_day();
    REQUIRE(carrot.symbol() == "v"); // sprouts after 1 day
    REQUIRE_FALSE(carrot.is_mature());

    // Day 2 end → mature
    carrot.end_day();
    REQUIRE(carrot.symbol() == "V");
    REQUIRE(carrot.is_mature());
}

// Test 3: Watering accelerates growth (counts as +2 days when day ends)
TEST_CASE("Carrot matures faster when watered") {
    Carrot carrot;

    // Water on day 0
    carrot.water();
    carrot.end_day(); // should count as 2 days of growth total

    // It should already be mature because watering advanced growth by 2 days
    REQUIRE(carrot.is_mature());
    REQUIRE(carrot.symbol() == "V");
}

// Test 4: Watering multiple times in same day has no extra effect
TEST_CASE("Multiple watering in same day does not stack") {
    Carrot carrot;

    carrot.water();
    carrot.water(); // second water shouldn't stack
    carrot.end_day();

    // Watering once or multiple times should still only add 2 days of growth
    REQUIRE(carrot.is_mature());
    REQUIRE(carrot.symbol() == "V");
}

// Test 5: After maturity, additional days don't change symbol
TEST_CASE("Carrot stays mature after reaching maturity") {
    Carrot carrot;

    carrot.end_day(); // sprout
    carrot.end_day(); // mature
    carrot.end_day(); // extra day
    REQUIRE(carrot.is_mature());
    REQUIRE(carrot.symbol() == "V");
}
