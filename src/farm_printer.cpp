#include "farm_printer.hpp"
#include "farm.hpp"
#include <string>

FarmPrinter::FarmPrinter(Farm* farm) : farm(farm) {}

std::string FarmPrinter::pp() {

    std::string output = "Legend:      @=Player     .=Soil     x=Seed/tilled     v/V=Carrot (v=seedling, V=mature)\n";
    output += "             o/O=Lettuce     s/S=Spinach     u/U=Beet     b/B=Brussels Sprouts\n\n";
    output += "Controls:    w=up   s=down   a=left   d=right   1=plant carrot   2=plant lettuce   3=plant spinach\n";
    output += "             4=plant beet   5=plant brussels   t=water   h=harvest   e=end day   q=quit\n\n";
    output += "Day " + std::to_string(farm->day()) + "\n";

    for (int i = 0; i < farm->number_of_rows(); i++) {
        for (int j = 0; j < farm->number_of_columns(); j++) {
            output += farm->get_symbol(i, j) + " ";
        }
        output += "\n";
    }
    return output;
}