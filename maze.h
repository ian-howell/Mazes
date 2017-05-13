#ifndef MAZE_H
#define MAZE_H
#include "cell.h"

#include <vector>

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

  char& at (const int i, const int j) { return grid[i][j]; }

  char& operator()(const int i, const int j) { return grid[i][j]; }
  const char& operator()(const int i, const int j) const { return grid[i][j]; }

  void init_curses();

  void print(const char* filename);

  void draw();

  std::vector<Cell> get_neighbors(Cell* cell);

  bool is_pathable(int r, int c);
  bool is_valid(int r, int c);
};
#endif
