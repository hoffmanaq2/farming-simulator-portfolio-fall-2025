#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/farm_printer.hpp"

TEST_CASE( "it pretty prints a single plot of land" ) {
    Player player;
    Farm farm(1, 1, &player);
    FarmPrinter printer(&farm);
    REQUIRE( printer.pp() == "@ \n" );
}

TEST_CASE( "it pretty prints a 1x2 farm" ) {
    Player player;
    Farm farm(1, 2, &player);
    FarmPrinter printer(&farm);
    REQUIRE( printer.pp() == "@ . \n" );
}

TEST_CASE( "it pretty prints a 2x1 farm" ) {
    Player player;
    Farm farm(2, 1, &player);
    FarmPrinter printer(&farm);
    REQUIRE( printer.pp() == "@ \n. \n" );
}

TEST_CASE( "it pretty prints a 2x2 farm" ) {
    Player player;
    Farm farm(2, 2, &player);
    FarmPrinter printer(&farm);
    REQUIRE( printer.pp() == "@ . \n. . \n" );
}