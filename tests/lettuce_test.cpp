#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/lettuce.hpp"

//Filer
TEST_CASE ("Carrot returns a v when it is a seedling") {
    Carrot carrot;
    REQUIRE( carrot.symbol() == "v" );
    REQUIRE_FALSE(carrot.is_mature());
}