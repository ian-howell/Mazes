#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdio.h>

#include "cell.h"
#include "maze.h"
#include "generator.h"

Generator::Generator(Maze* maze)
{
  this->maze = maze;
  srand(time(NULL));
}

void Generator::create_maze(bool animate)
{
  if (animate)
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

    clear();
  }

  char** grid = maze->get_grid();
  int rows = maze->get_rows();
  int cols = maze->get_cols();
  Cell start(0, 0, NULL);

  grid[start.row][start.col] = 'S';

  std::vector<Cell *> frontier;

  // Add the start node's neighbors to the frontier
  frontier.push_back(new Cell(start.row + 1, start.col, &start));
  frontier.push_back(new Cell(start.row, start.col + 1, &start));

  Cell* child;
  Cell* gc;
  std::vector<Cell *> grandchildren;
  bool gc_used = false;

  while (!frontier.empty())
  {
    int rand_point = rand() % frontier.size();
    child = frontier[rand_point];
    frontier.erase(frontier.begin() + rand_point);

    gc = child->get_child();
    int r = gc->row;
    int c = gc->col;

    if (maze->is_valid(r, c) && grid[r][c] == '#')
    {
      grid[child->row][child->col] = ' ';
      grid[r][c] = 'E';

      for (int i = -1; i <= 1; i += 2)
      {
        if (maze->is_valid(r + i, c))
        {
          frontier.push_back(new Cell(r + i, c, gc));
          gc_used = true;
        }

        if (maze->is_valid(r, c + i))
        {
          frontier.push_back(new Cell(r, c + i, gc));
          gc_used = true;
        }
      }

      if (animate)
      {
        maze->draw();
        usleep(DRAW_DELAY);
      }

      grid[r][c] = ' ';
    }

    delete child;

    (!gc_used) ?  delete gc : grandchildren.push_back(gc);
  }

  grid[rows - 1][cols - 1] = 'E';
  if (animate)
  {
    maze->draw();
    usleep(DRAW_DELAY);
    getch();
    endwin();
  }

  for (int i = 0; i < (int)grandchildren.size(); i++)
  {
    delete grandchildren[i];
  }
  return;
}
