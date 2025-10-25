#include "farm_printer.hpp"
#include "farm.hpp"
#include <string>

FarmPrinter::FarmPrinter(Farm* farm) : farm(farm) {}

std::string FarmPrinter::pp() {

    std::string output = "Legend:      @=Player     .=Soil      v=Baby Carrot       V=Mature Carrot\n\n";
    output += "Controls:    w=up   s=down   a=left   d=right   c=plant   h=harvest   e=end day   q=quit\n\n"; //3 spaces
    output += "Day " + std::to_string(farm->day()) + "\n";

    for (int i = 0; i < farm->number_of_rows(); i++) {
        for (int j = 0; j < farm->number_of_columns(); j++) {
            output += farm->get_symbol(i, j) + " ";
        }
        output += "\n";
    }
    return output;
}