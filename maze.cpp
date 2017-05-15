#include <cstdio>
#include <ncurses.h>
#include <unistd.h>
#include "maze.h"

Maze::Maze(int nrows, int ncols)
{
  rows = (nrows % 2) ? nrows : nrows - 1;
  cols = (ncols % 2) ? ncols : ncols - 1;
  for (int i = 0; i < rows; i++)
  {
    std::vector<char> temp_row;
    for (int j = 0; j < cols; j++)
    {
      temp_row.push_back('#');
    }
    grid.push_back(temp_row);
  }
}

Maze::Maze(const char* filename)
{
  FILE* f = fopen(filename, "r");
  fscanf(f, "%d %d\n", &rows, &cols);

  char dummy;
  for (int i = 0; i < rows; i++)
  {
    std::vector<char> temp_row;
    for (int j = 0; j < cols; j++)
    {
      // Read in a character
      fscanf(f, "%c", &dummy);
      temp_row.push_back(dummy);

      if (dummy == 'S')
        start = CellPtr(new Cell(i, j, NULL));
      else if (dummy == 'E')
        end = CellPtr(new Cell(i, j, NULL));
    }
    // Read in the new line
    fscanf(f, "%c", &dummy);

    // Store the new row in the grid
    grid.push_back(temp_row);
  }
  fclose(f);
}

Maze::~Maze()
{
  /* Intentionally left empty */
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

std::vector<CellPtr> Maze::get_neighbors(CellPtr cell)
{
  std::vector<CellPtr> neighbors;
  int new_row;
  int new_col;
  int offset[4][2] = {
    {-1, 0},
    {0, +1},
    {+1, 0},
    {0, -1}
  };
  for (int i = 0; i < 4; i++)
  {
    new_row = cell->row + offset[i][0];
    new_col = cell->col + offset[i][1];
    if (is_pathable(new_row, new_col))
      neighbors.push_back(CellPtr(new Cell(new_row, new_col, cell)));
  }
  return neighbors;
}

bool Maze::is_pathable(int r, int c)
{
  return (is_valid(r, c)) && ((grid[r][c] == ' ') || (grid[r][c] == 'E'));
}

bool Maze::is_valid(int r, int c)
{
  return r >= 0 && r < rows && c >= 0 && c < cols;
}

void Maze::maybe_init(bool animate)
{
  if (animate)
  {
    init_curses();
    draw();
  }
  return;
}

void Maze::maybe_endwin(bool animate)
{
  if (animate)
  {
    getch();
    endwin();
  }
  return;
}

void Maze::maybe_draw(bool animate)
{
  if (animate)
  {
    draw();
    usleep(draw_delay);
  }
  return;
}

int Maze::draw_delay = DRAW_DELAY;
