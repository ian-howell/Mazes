#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include "cell.h"
#include <memory>
#include <vector>

class Solver
{
 public:
  typedef char solve_t;
  enum
  {
    BFS,
    DFS,
    BACKTRACKING,
    ASTAR,
    PLAY
  };

  Solver();

  void solve(MazePtr maze, solve_t algorithm, bool animate=true);

 private:
  bool backtrack(MazePtr maze, bool animate=true);
  bool X_first_search(MazePtr maze, solve_t solve_type, bool animate=true);
  void player_control(MazePtr maze);
  bool astar(MazePtr maze, bool animate=true);

  bool backtrack_r(MazePtr maze, CellPtr cell, bool animate);
  int manhattan_distance(CellPtr first, CellPtr second);
  int real_distance(CellPtr first, CellPtr second);
  void mouse_control(MazePtr maze, bool animate=true);
};

#endif
