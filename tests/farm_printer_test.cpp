#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/farm_printer.hpp"


TEST_CASE("FarmPrinter prints expected farm layout (2x2) and legend") {
    Player player;
    Farm farm(2, 2, &player);
    FarmPrinter printer(&farm);

    std::string expected;
    expected += "Legend:      @=Player     .=Soil     x=Seed/tilled     v/V=Carrot (v=seedling, V=mature)\n";
    expected += "             o/O=Lettuce     s/S=Spinach     u/U=Beet     b/B=Brussels Sprouts\n\n";
    expected += "Controls:    w=up   s=down   a=left   d=right   1=plant carrot   2=plant lettuce   3=plant spinach\n";
    expected += "             4=plant beet   5=plant brussels   t=water   h=harvest   e=end day   q=quit\n\n";
    expected += "Day " + std::to_string(farm.day()) + "\n";

    // Farm grid (2 rows, 2 columns)
    expected += "@ . \n";
    expected += ". . \n";

    REQUIRE(printer.pp() == expected);
}
//Next portfolio - will want to add "L" to display legend, and not legend on screen entire time
//With legend on screen, makes it difficult to write clear tests