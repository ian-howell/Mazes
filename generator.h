#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <ncurses.h>
#include "maze.h"

class Generator
{
 private:
   int rows;
   int cols;

  /**
   * animate
   *
   * Color the maze, then print it to the screen
   */
  void animate();

 public:
  Generator(int r, int c);

  /**
   * prims
   *
   * Uses Prim's algorithm to create a random path through the maze
   */
   MazePtr prims(bool animate=false);

   MazePtr dfs(bool animate=false);
};
#endif
