#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/soil.hpp"

TEST_CASE("Soil returns a dot as its symbol") {
    Soil soil;
    REQUIRE( soil.symbol() == "." );
}

TEST_CASE("Soil end_day does nothing") {
    Soil soil;
    soil.end_day(); // Should not throw or change state
    REQUIRE(soil.symbol() == ".");
}