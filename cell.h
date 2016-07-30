#ifndef CELL_H
#define CELL_H

class Cell
{
    public:
        int row;
        int col;
        Cell *parent;

        Cell(int row, int col, Cell *parent);
        Cell* get_opposite();
};

bool is_valid(int r, int c, int max_row, int max_col);

#endif
