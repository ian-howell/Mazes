#include "cell.h"
#define NULL 0

Cell::Cell()
{
  /* Intentionally left empty */
}

Cell::Cell(int row, int col, CellPtr parent)
{
  this->row = row;
  this->col = col;
  this->parent = parent;
}

CellPtr Cell::get_child()
{
  return CellPtr(new Cell((row << 1) - parent->row,
                          (col << 1) - parent->col,
                          NULL));
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
  return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}
