#include <cstdio>
#include <ncurses.h>
#include "maze.h"

Maze::Maze(int rows, int cols)
{
  rows = (rows % 2) ? rows : rows - 1;
  cols = (cols % 2) ? cols : cols - 1;
  grid = new char*[rows];
  for (int i = 0; i < rows; i++)
  {
    grid[i] = new char[cols];
    for (int j = 0; j < cols; j++)
    {
      grid[i][j] = '#';
    }
  }
}

Maze::Maze(const char* filename)
{
  FILE* f = fopen(filename, "r");
  fscanf(f, "%d %d\n", &rows, &cols);

  grid = new char*[rows];

  char dummy;
  for (int i = 0; i < rows; i++)
  {
    grid[i] = new char[cols];
    for (int j = 0; j < cols; j++)
    {
      fscanf(f, "%c", &grid[i][j]);
    }
    fscanf(f, "%c", &dummy);
  }
  fclose(f);
}

Maze::~Maze()
{
  // Delete the grid
  for (int i = 0; i < rows; i++)
  {
    delete [] grid[i];
    grid[i] = nullptr;
  }
  delete [] grid;
  grid = nullptr;
}

void Maze::print(const char* filename)
{
  FILE* f = fopen(filename, "w");
  fprintf(f, "%d %d\n", rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      fprintf(f, "%c", grid[i][j]);
    }
    fprintf(f, "\n");
  }
  fclose(f);
  return;
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
