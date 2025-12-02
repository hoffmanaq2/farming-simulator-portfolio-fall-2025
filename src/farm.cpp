#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "farm.hpp"
#include "carrot.hpp"
#include "lettuce.hpp"
#include "spinach.hpp"
#include "beet.hpp"
#include "brussels_sprouts.hpp"
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
  srand(time(NULL));
}

Farm::~Farm() {
  for (std::vector<Plot*>& row : plots) {
    for (Plot* plot : row) {
      delete plot;
    }
  }
  if (bunny != nullptr)
    delete bunny;
}

int Farm::number_of_rows() { return rows; }
int Farm::number_of_columns() { return columns; }
int Farm::day() const { return current_day; }

// std::string Farm::get_symbol(int row, int column) {
//   if(player->row() == row && player->column() == column) {
//     return "@";
//   } else {
//     return plots.at(row).at(column)->symbol(); //not needed?
//   }
// }

std::string Farm::get_symbol(int row, int column) {
  if (player->row() == row && player->column() == column)
    return "@";
  if (bunny != nullptr && bunny->row() == row && bunny->column() == column)
    return "R";
  return plots.at(row).at(column)->symbol();
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

void Farm::water(int row, int column) {
  // if soil, water does nothing (handled by overridden water methods)
  plots.at(row).at(column)->water();
}

// BUNNY LOGIC
void Farm::maybe_spawn_bunny() {
  if (bunny != nullptr)
    return;

  int chance = rand() % 4; // 25% chance
  if (chance != 0)
    return;

  int edge = rand() % 4;
  int r = 0;
  int c = 0;

  if (edge == 0) { r = 0; c = rand() % columns; }
  else if (edge == 1) { r = rows - 1; c = rand() % columns; }
  else if (edge == 2) { r = rand() % rows; c = 0; }
  else { r = rand() % rows; c = columns - 1; }

  bunny = new Bunny(r, c);
}

void Farm::bunny_eat_if_plant() {
  if (bunny == nullptr)
    return;

  if (plots.at(bunny->row()).at(bunny->column())->symbol() != ".") {
    delete plots.at(bunny->row()).at(bunny->column());
    plots.at(bunny->row()).at(bunny->column()) = new Soil();
  }
}

void Farm::bunny_check_fear() {
  if (bunny == nullptr)
    return;

  int pr = player->row();
  int pc = player->column();
  int br = bunny->row();
  int bc = bunny->column();

  if ((pr == br - 1 && pc == bc) || (pr == br + 1 && pc == bc) ||
      (pr == br && pc == bc - 1) || (pr == br && pc == bc + 1)) {
    bunny->scare();
      }
}

void Farm::bunny_move() {
  if (bunny == nullptr)
    return;

  int br = bunny->row();
  int bc = bunny->column();

  if (bunny->is_scared()) {
    int dr = br - player->row();
    int dc = bc - player->column();

    if (dr > 0) br += 4;
    else if (dr < 0) br -= 4;

    if (dc > 0) bc += 4;
    else if (dc < 0) bc -= 4;

    bunny->calm_down();
  } else {
    int dir = rand() % 4;
    if (dir == 0) br--;
    else if (dir == 1) br++;
    else if (dir == 2) bc--;
    else bc++;
  }

  if (br < 0 || br >= rows || bc < 0 || bc >= columns) {
    delete bunny;
    bunny = nullptr;
    return;
  }

  if (!(br == player->row() && bc == player->column())) {
    bunny->set_row(br);
    bunny->set_column(bc);
  }
}

void Farm::end_day() {
  current_day++;
  for (std::vector<Plot*>& row : plots) {
    for (Plot* plot : row) {
      plot->end_day();
    }
  }
  bunny_eat_if_plant();
  bunny_check_fear();
  bunny_move();
  maybe_spawn_bunny();
}