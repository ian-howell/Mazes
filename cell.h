#ifndef CELL_H
#define CELL_H

class Cell
{
 public:
  int row;
  int col;
  Cell *parent;

  Cell();
  Cell(int row, int col, Cell *parent);
  Cell* get_child();
};

#endif
