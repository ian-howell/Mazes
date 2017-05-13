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
   * create_maze
   *
   * Uses Prim's algorithm to create a random path through the maze
   */
   MazePtr create_maze(bool animate=false);
};
#endif
