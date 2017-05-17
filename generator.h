#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <ncurses.h>
#include "maze.h"

class Generator
{
 private:
   int rows;
   int cols;

 public:
  Generator(int r, int c);

  /**
   * prims
   *
   * Uses Prim's algorithm to create a random path through the maze
   */
   MazePtr prims(bool animate=false);

   MazePtr dfs(bool animate=false);

   MazePtr kruskal(bool animate=false);

   void finished(MazePtr maze, bool animate=false);
};
#endif
