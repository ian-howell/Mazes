#ifndef MAZE_H
#define MAZE_H
#include "cell.h"

#include <memory>
#include <vector>

#define DRAW_DELAY 50000

// Forward declarations
class Maze;

typedef std::shared_ptr<Maze> MazePtr;

typedef std::vector<std::vector<char>> GridPtr;

class Maze
{
 private:
  int rows;
  int cols;
  GridPtr grid;
  CellPtr start;
  CellPtr end;

 public:
  Maze(int nrow, int ncol);
  Maze(const char* filename);
  ~Maze();

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  CellPtr get_start() const { return start; }
  CellPtr get_end()   const { return end;   }

  char& at (const int i, const int j) { return grid[i][j]; }

  char& operator()(const int i, const int j) { return grid[i][j]; }
  const char& operator()(const int i, const int j) const { return grid[i][j]; }

  void init_curses();
  void maybe_init(bool animate=true);
  void maybe_endwin(bool animate=true);
  void maybe_draw(bool animate=true);

  void print(const char* filename);

  void draw();

  std::vector<CellPtr> get_neighbors(CellPtr cell);

  bool is_pathable(int r, int c);
  bool is_valid(int r, int c);

  static int draw_delay;
};
#endif
