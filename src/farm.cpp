#include <string>
#include <vector>

#include "farm.hpp"
#include "carrot.hpp"
#include "lettuce.hpp"
#include "spinach.hpp"
#include "beet.hpp"
#include "brussels_sprouts.hpp"
//#include "water.hpp"
#include "soil.hpp"

Farm::Farm(int rows, int columns, Player *player) : rows(rows), columns(columns), player(player) {
  for(int i = 0; i < rows; i++) {
    std::vector<Plot *> row;
    for(int j = 0; j < columns; j++) {
      Soil *soil = new Soil();
      row.push_back(soil);
    }
    plots.push_back(row);
  }
}

Farm::~Farm() {
  for (std::vector<Plot*>& row : plots) {
    for (Plot* plot : row) {
      delete plot;
    }
  }
}

int Farm::number_of_rows() { return rows; }
int Farm::number_of_columns() { return columns; }
int Farm::day() const { return current_day; }

std::string Farm::get_symbol(int row, int column) {
  if(player->row() == row && player->column() == column) {
    return "@";
  } else {
    return plots.at(row).at(column)->symbol(); //not needed?
  }
}

void Farm::plant(int row, int column, Plot *plot) {
  //cannot plant on non-soil
  if (dynamic_cast<Soil*>(plots.at(row).at(column)) == nullptr)
    return;
    delete plots.at(row).at(column);
    plots.at(row).at(column) = plot;
  }

void Farm::harvest(int row, int column) {
  if (plots.at(row).at(column)->is_mature()) {
    delete plots.at(row).at(column);
    plots.at(row).at(column) = new Soil();
  }
}

void Farm::end_day() {
  current_day++;
  for (std::vector<Plot*>& row : plots) {
    for (Plot* plot : row) {
      plot->end_day();
    }
  }
}

void Farm::water(int row, int column) {
  // if soil, water does nothing (handled by overridden water methods)
  plots.at(row).at(column)->water();
}
