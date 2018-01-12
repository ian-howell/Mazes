#ifndef PLAYER_H
#define PLAYER_H
#include "maze.h"

class Player
{
 private:
  int row;
  int col;

  bool is_valid(MazePtr maze, int row, int col);
 public:
  typedef unsigned char direction;
  enum
  {
    LEFT,
    RIGHT,
    UP,
    DOWN
  };


  Player(int row, int col);
  bool move(MazePtr maze, direction dir);
};
#endif
