#ifndef PLAYER_H
#define PLAYER_H
#include "maze.h"

typedef unsigned char direction;
enum
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Player
{
 private:
  int row;
  int col;

  Maze* maze;

  void init_grid(Maze* maze);
  bool is_valid(int row, int col);
 public:
  bool game_won;

  Player(Maze* maze, int row, int col);
  void move(direction dir);

};
#endif
