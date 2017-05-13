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

  bool game_won;

  Player(int row, int col);
  void move(MazePtr maze, direction dir);

};
#endif
