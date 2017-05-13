#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include "cell.h"
#include <vector>

class Solver
{
 private:
  char** grid;
  Cell start;
  Cell end;

  Maze* maze;

  bool backtrack_r(Cell cell, bool animate);
  bool is_valid(int row, int col);

 public:

  typedef char SOLVE_TYPE;
  enum
  {
    BFS,
    DFS,
    BACKTRACKING,
    ASTAR
  };

  Solver(Maze* maze);
  bool backtrack(bool animate=true);
  void X_first_search(SOLVE_TYPE solve_type, bool animate=true);
  void player_control();
};

enum
{
  EAST,
  SOUTH,
  WEST,
  NORTH
};

std::vector<Cell> get_neighbors(Cell* node, const int max_row, const int max_col);

#endif
