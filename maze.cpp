#include <cstdio>
#include <ncurses.h>
#include "maze.h"

Maze::Maze(int rows, int cols)
{
  this->rows = (rows % 2) ? rows : rows - 1;
  this->cols = (cols % 2) ? cols : cols - 1;
  grid = new char*[this->rows];
  for (int i = 0; i < this->rows; i++)
  {
    grid[i] = new char[this->cols];
    for (int j = 0; j < this->cols; j++)
    {
      grid[i][j] = '#';
    }
  }
}

Maze::~Maze()
{
  // Delete the grid
  for (int i = 0; i < rows; i++)
    delete [] grid[i];
  delete [] grid;
}

void Maze::print()
{
  printf("%d %d\n", rows + 2, cols + 2);
  for (int i = 0; i < cols + 2; i++)
  {
    printf("#");
  }
  printf("\n");
  for (int i = 0; i < rows; i++)
  {
    printf("#");
    for (int j = 0; j < cols; j++)
    {
      printf("%c", grid[i][j]);
    }
    printf("#\n");
  }
  for (int i = 0; i < cols + 2; i++)
  {
    printf("#");
  }
  printf("\n");
}

void Maze::draw()
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (grid[i][j] == '#')
        attron(COLOR_PAIR(1));
      else if (grid[i][j] == ' ')
        attron(COLOR_PAIR(2));
      else if (grid[i][j] == '.')
        attron(COLOR_PAIR(5));
      else if (grid[i][j] == 'S')
        attron(COLOR_PAIR(3));
      else
        attron(COLOR_PAIR(4));

      mvwprintw(stdscr, i + 1, j + 1, "%c", grid[i][j]);

      attroff(COLOR_PAIR(1));
      attroff(COLOR_PAIR(2));
      attroff(COLOR_PAIR(3));
      attroff(COLOR_PAIR(4));
      attroff(COLOR_PAIR(5));
    }
  }
  refresh();
}

bool Maze::is_valid(int r, int c)
{
  return r >= 0 && r < rows && c >= 0 && c < cols;
}
