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

  char** grid = maze->get_grid();

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

  if (grid[newrow][newcol] == 'E')
  {
    game_won = true;
    grid[midrow][midcol] = '.';
    grid[row][col] = '.';
    return;
  }
  else if (grid[newrow][newcol] == '.')
  {
    grid[midrow][midcol] = ' ';
    grid[row][col] = ' ';
  }
  else
  {
    grid[midrow][midcol] = '.';
    grid[row][col] = '.';
  }

  // Print the player in the new location
  row = newrow;
  col = newcol;
  grid[row][col] = 'S';
}

bool Player::is_valid(int row, int col)
{
  bool retval = true;

  if (maze->is_valid(row, col))
  {
    if (maze->get_grid()[row][col] == '#')
      retval = false;
  }
  else
  {
    retval = false;
  }

  return retval;
}
