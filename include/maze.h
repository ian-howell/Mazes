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
  bool animate_flag;

 public:
  typedef char cell_t;
  enum
  {
    WALL,
    FLOOR
  };

  Maze(int nrow, int ncol, bool animate=false);
  Maze(const char* filename, bool animate=false);
  ~Maze();

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  int get_index(CellPtr cell) const;

  CellPtr get_start() const { return start; }
  CellPtr get_end()   const { return end;   }

  void set_start(int r, int c);
  void set_end(int r, int c);

  char& at (const int i, const int j) { return grid[i][j]; }

  char& operator()(const int i, const int j) { return grid[i][j]; }
  const char& operator()(const int i, const int j) const { return grid[i][j]; }

  void init_curses();
  void end_curses();
  void message(const char* msg);

  void print(const char* filename);

  void draw(int delay=0);

  std::vector<CellPtr> get_neighbors(CellPtr cell, cell_t cell_type,
      bool diag=false);

  bool is_pathable(int r, int c);
  bool is_valid(int r, int c);
  bool is_wall(int r, int c);

  void clear();

  static int draw_delay;
};
#endif
