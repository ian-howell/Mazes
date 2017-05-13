#ifndef MAZE_H
#define MAZE_H
#include "cell.h"

#define DRAW_DELAY 50000

class Maze
{
 private:
  int rows;
  int cols;
  char** grid;
  Cell start;
  Cell end;

 public:
  Maze(int nrow, int ncol);
  Maze(const char* filename);
  ~Maze();

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  Cell get_start() const { return start; }
  Cell get_end()   const { return end;   }

  char** get_grid() const { return grid; }

  void init_curses();

  void print(const char* filename);

  void draw();

  bool is_valid(int r, int c);
};
#endif
