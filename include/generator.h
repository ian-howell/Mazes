#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <ncurses.h>
#include "maze.h"

class Generator
{
 public:
  typedef char generate_t;
  enum
  {
    DFS,
    PRIMS,
    KRUSKALS
  };

  Generator(int r, int c);

  MazePtr generate(generate_t algorithm, bool animate=true);

 private:
  int rows;
  int cols;

  void prims(MazePtr maze, bool animate);
  void dfs(MazePtr maze, bool animate);
  void kruskals(MazePtr maze, bool animate);

  void finished(MazePtr maze, bool animate);
};
#endif
