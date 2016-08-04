#include "cell.h"
#define NULL 0

Cell::Cell(int row, int col, Cell* parent)
{
    this->row = row;
    this->col = col;
    this->parent = parent;
}

Cell* Cell::get_child()
{
    return new Cell((row << 1) - parent->row, (col << 1) - parent->col, NULL);
}

bool is_valid(int r, int c, int max_row, int max_col)
{
    return r >= 0 && r < max_row && c >= 0 && c < max_col;
}

