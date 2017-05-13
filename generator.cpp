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
    maze->init_curses();
    clear();
  }

  int rows = maze->get_rows();
  int cols = maze->get_cols();
  Cell start(0, 0, NULL);

  (*maze)(start.row, start.col) = 'S';

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

    if (maze->is_valid(r, c) && (*maze)(r, c) == '#')
    {
      (*maze)(child->row, child->col) = ' ';
      (*maze)(r, c) = 'E';

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

      (*maze)(r, c) = ' ';
    }

    delete child;

    (!gc_used) ?  delete gc : grandchildren.push_back(gc);
  }

  (*maze)(rows - 1, cols - 1) = 'E';
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
