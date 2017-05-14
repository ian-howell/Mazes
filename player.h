#ifndef PLAYER_H
#define PLAYER_H
#include "maze.h"

class Player
{
 private:
  int row;
  int col;
  bool win_flag;

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
  void move(MazePtr maze, direction dir);
  bool game_won() { return win_flag; }
};
#endif
