#include "cell.h"
#define NULL 0

Cell::Cell()
{
  /* Intentionally left empty */
}

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
