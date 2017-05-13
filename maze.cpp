#include <cstdio>
#include <ncurses.h>
#include "maze.h"

Maze::Maze(int nrows, int ncols)
{
  rows = (nrows % 2) ? nrows : nrows - 1;
  cols = (ncols % 2) ? ncols : ncols - 1;
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
      if (grid[i][j] == 'S')
        start = Cell(i, j, NULL);
      else if (grid[i][j] == 'E')
        end = Cell(i, j, NULL);
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

void Maze::init_curses()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_BLUE, COLOR_BLUE);
  init_pair(4, COLOR_RED, COLOR_RED);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);

}

void Maze::print(const char* filename)
{
  FILE* f = fopen(filename, "w");
  fprintf(f, "%d %d\n", rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      switch(grid[i][j])
      {
        case 'S':
          fprintf(f, "S");
          break;
        case 'E':
          fprintf(f, "E");
          break;
        case '#':
          fprintf(f, "#");
          break;
        case '*':
          fprintf(f, ".");
          break;
        default:
          fprintf(f, " ");
      }
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
      else if (grid[i][j] == ',' || grid[i][j] == '*')
        attron(COLOR_PAIR(6));
      else
        attron(COLOR_PAIR(4));

      mvwprintw(stdscr, i + 1, j + 1, "%c", grid[i][j]);

      attroff(COLOR_PAIR(1));
      attroff(COLOR_PAIR(2));
      attroff(COLOR_PAIR(3));
      attroff(COLOR_PAIR(4));
      attroff(COLOR_PAIR(5));
      attroff(COLOR_PAIR(6));
    }
  }
  refresh();
}

bool Maze::is_pathable(int r, int c)
{
  return (is_valid(r, c)) && ((grid[r][c] == ' ') || (grid[r][c] == 'E'));
}

bool Maze::is_valid(int r, int c)
{
  return r >= 0 && r < rows && c >= 0 && c < cols;
}
