#include <ncurses.h>
#include "player.h"
#include "maze.h"

Player::Player(Maze* maze, int row, int col)
{
  this->game_won = false;
  this->row = row;
  this->col = col;

  this->maze = maze;
}

void Player::move(direction dir)
{
  int midcol = col;
  int midrow = row;
  int newcol = col;
  int newrow = row;

  switch (dir)
  {
    case LEFT:
      if (is_valid(row, col - 1))
      {
        midcol--;
        newcol -= 2;
      }
      break;
    case RIGHT:
      if (is_valid(row, col + 1))
      {
        midcol++;
        newcol += 2;
      }
      break;
    case UP:
      if (is_valid(row - 1, col))
      {
        midrow--;
        newrow -= 2;
      }
      break;
    case DOWN:
      if (is_valid(row + 1, col))
      {
        midrow++;
        newrow += 2;
      }
      break;
  }

  if ((newcol == col) && (newrow == row))
    return;

  if (maze->at(newrow, newcol) == 'E')
  {
    game_won = true;
    maze->at(midrow, midcol) = '.';
    maze->at(row, col) = '.';
    return;
  }
  else if (maze->at(newrow, newcol) == '.')
  {
    maze->at(midrow, midcol) = ' ';
    maze->at(row, col) = ' ';
  }
  else
  {
    maze->at(midrow, midcol) = '.';
    maze->at(row, col) = '.';
  }

  // Print the player in the new location
  row = newrow;
  col = newcol;
  maze->at(row, col) = 'S';
}

bool Player::is_valid(int row, int col)
{
  return (maze->is_valid(row, col)) && maze->at(row, col) != '#';
}
