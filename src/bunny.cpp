#include "bunny.hpp"

Bunny::Bunny(int row, int column) : current_row(row), current_column(column) {}

int Bunny::row() { return current_row; }
int Bunny::column() { return current_column; }

void Bunny::set_row(int r) { current_row = r; }
void Bunny::set_column(int c) { current_column = c; }

bool Bunny::is_scared() { return scared; }
void Bunny::scare() { scared = true; }
void Bunny::calm_down() { scared = false; }