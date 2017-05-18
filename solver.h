#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include "cell.h"
#include <memory>
#include <vector>

class Solver
{
 private:
  bool backtrack_r(MazePtr maze, CellPtr cell, bool animate);
  int manhattan_distance(CellPtr first, CellPtr second);
  int real_distance(CellPtr first, CellPtr second);
  void mouse_control(MazePtr maze, bool animate=true);

 public:
  typedef char SOLVE_TYPE;
  enum
  {
    BFS,
    DFS,
    BACKTRACKING,
    ASTAR
  };

  Solver();
  bool backtrack(MazePtr maze, bool animate=true);
  void X_first_search(MazePtr maze, SOLVE_TYPE solve_type, bool animate=true);
  void player_control(MazePtr maze);
  bool astar(MazePtr maze, bool animate=true);
};

#endif
