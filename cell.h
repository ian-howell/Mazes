#ifndef CELL_H
#define CELL_H
#include <memory>

// Forward declarations
class Cell;

typedef std::shared_ptr<Cell> CellPtr;

class Cell
{
 public:
  int row;
  int col;
  CellPtr parent;

  Cell();
  Cell(int row, int col, CellPtr parent);
  CellPtr get_child();

  friend bool operator==(const Cell& lhs, const Cell& rhs);
};

#endif
