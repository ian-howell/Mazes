#include <cstdio>
#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include "maze.h"

Maze::Maze(int nrows, int ncols, bool animate) :
  animate_flag(animate)
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
  start = nullptr;
  end = nullptr;
}

Maze::Maze(const char* filename, bool animate) :
  animate_flag(animate)
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

int Maze::get_index(CellPtr cell) const
{
  return cell->col + (cell->row * cols);
}

void Maze::set_start(int r, int c)
{
  if (is_pathable(r, c))
  {
    // Get rid of old start character
    if (start != nullptr)
      grid[start->row][start->col] = ' ';

    start = CellPtr(new Cell(r, c, NULL));
    grid[r][c] = 'S';
  }
}

void Maze::set_end(int r, int c)
{
  if (is_pathable(r, c))
  {
    // Get rid of old end character
    if (end != nullptr)
      grid[end->row][end->col] = ' ';

    end = CellPtr(new Cell(r, c, NULL));
    grid[r][c] = 'E';
  }
}

void Maze::init_curses()
{
  if (animate_flag)
  {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_YELLOW, COLOR_YELLOW);
  }
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

void Maze::draw(int delay)
{
  if (animate_flag)
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        switch(grid[i][j])
        {
          case '#':
            attron(COLOR_PAIR(1));
            break;
          case ' ':
            attron(COLOR_PAIR(2));
            break;
          case '.':
            attron(COLOR_PAIR(5));
            break;
          case 'S':
            attron(COLOR_PAIR(3));
            break;
          case ',':
            attron(COLOR_PAIR(7));
            break;
          case '*':
            attron(COLOR_PAIR(6));
            break;
          default:
            attron(COLOR_PAIR(4));
        }

        mvwprintw(stdscr, i + 1, j + 1, "%c", grid[i][j]);

        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(4));
        attroff(COLOR_PAIR(5));
        attroff(COLOR_PAIR(6));
        attroff(COLOR_PAIR(7));
      }
    }
    refresh();
    usleep(draw_delay);
  }
}

std::vector<CellPtr> Maze::get_neighbors(CellPtr cell, cell_t cell_type,
    bool diag)
{
  std::vector<CellPtr> neighbors;
  int new_row;
  int new_col;
  int offset[8][2] = {
    {-1, 0},  // UP
    {+1, 0},  // DOWN
    {0, +1},  // RIGHT
    {0, -1},  // LEFT

    /* Only used if diag is set */
    {-1, -1}, // UP-LEFT
    {-1, +1}, // UP-RIGHT
    {+1, +1}, // DOWN-RIGHT
    {+1, -1}, // DOWN-LEFT
  };
  int limit = diag ? 8 : 4;
  for (int i = 0; i < limit; i++)
  {
    new_row = cell->row + offset[i][0];
    new_col = cell->col + offset[i][1];
    bool valid_floor = (cell_type == FLOOR) && is_pathable(new_row, new_col);
    bool valid_wall = (cell_type == WALL) && (is_wall(new_row, new_col));
    if (valid_floor || valid_wall)
      neighbors.push_back(CellPtr(new Cell(new_row, new_col, cell)));
  }
  return neighbors;
}

bool Maze::is_pathable(int r, int c)
{
  return (is_valid(r, c)) && (grid[r][c] != '#') && (grid[r][c] != '.');
}

bool Maze::is_valid(int r, int c)
{
  return r >= 0 && r < rows && c >= 0 && c < cols;
}

bool Maze::is_wall(int r, int c)
{
  return is_valid(r, c) && grid[r][c] == '#';
}

void Maze::end_curses()
{
  if (animate_flag)
  {
    endwin();
  }
  return;
}

void Maze::message(const char* msg)
{
  if (animate_flag)
  {
    // Clear the "message buffer"
    wmove(stdscr, rows+1, 0);
    clrtoeol();

    mvwprintw(stdscr, rows+1, 0, msg);
    refresh();
  }
  return;
}

void Maze::clear()
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (grid[i][j] != '#')
      {
        grid[i][j] = ' ';
      }
    }
  }
  grid[start->row][start->col] = 'S';
  grid[end->row][end->col] = 'E';
  return;
}

int Maze::draw_delay = DRAW_DELAY;
