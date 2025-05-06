#include "board.h"

char Board::get_cell(int row, int col) const { return table[row][col]; }

void Board::set_cell(int row, int col, char value) { table[row][col] = value; }
