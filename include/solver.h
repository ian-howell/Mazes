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

  Solver(bool diag=false);

  void solve(MazePtr maze, solve_t algorithm, bool animate=true);
  void mouse_control(MazePtr maze, solve_t algorithm, bool animate=true);

 private:
  bool backtrack(MazePtr maze);
  bool X_first_search(MazePtr maze, solve_t solve_type);
  void player_control(MazePtr maze);
  bool astar(MazePtr maze);

  bool backtrack_r(MazePtr maze, CellPtr cell);
  double manhattan_distance(CellPtr first, CellPtr second);
  double real_distance(CellPtr first, CellPtr second);

  bool allow_diag;
};

#endif
