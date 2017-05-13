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

#endif
