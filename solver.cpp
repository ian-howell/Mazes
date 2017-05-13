#include <unistd.h>
#include "solver.h"
#include "cell.h"
#include "maze.h"
#include "player.h"
#include <cstdio>
#include <ncurses.h>
#include <vector>
#include <deque>

Solver::Solver(Maze* maze)
{
  this->maze = maze;
  grid = maze->get_grid();
  start = maze->get_start();
  end = maze->get_end();
}

bool Solver::backtrack(bool animate)
{
  bool ret_val;

  if (animate)
  {
    maze->init_curses();
    clear();
  }

  ret_val = backtrack_r(start, animate);

  if (animate)
  {
    getchar();
    endwin();
  }

  return ret_val;
}

bool Solver::backtrack_r(Cell cell, bool animate)
{
  std::vector<Cell> neighbors = get_neighbors(&cell, maze->get_rows(),
      maze->get_cols());
  for (size_t i = 0; i < neighbors.size(); i++)
  {
    int row = neighbors[i].row;
    int col = neighbors[i].col;
    if (maze->is_pathable(row, col))
    {
      if (grid[row][col] == 'E')
      {
        return true;
      }

      grid[row][col] = '*';

      if (animate)
      {
        maze->draw();
        usleep(DRAW_DELAY);
      }

      grid[row][col] = '.';

      if (backtrack_r(neighbors[i], animate))
      {
        grid[row][col] = '*';

        if (animate)
        {
          maze->draw();
          usleep(DRAW_DELAY);
        }
        return true;
      }
      else
      {
        grid[row][col] = '*';

        if (animate)
        {
          maze->draw();
          usleep(DRAW_DELAY);
        }
        grid[row][col] = ' ';
      }
    }
  }
  return false;
}

void Solver::X_first_search(SOLVE_TYPE solve_type, bool animate)
{
  std::deque<Cell*> frontier;
  std::deque<Cell*> to_delete;

  if (animate)
  {
    maze->init_curses();
    clear();
  }

  start.parent = NULL;
  frontier.push_back(&start);

  Cell* u;
  while (!frontier.empty())
  {
    if (solve_type == BFS)
    {
      u = frontier.front(); frontier.pop_front();
    }
    else
    {
      u = frontier.back(); frontier.pop_back();
    }

    if (u->row == end.row && u->col == end.col)
    {
      for (Cell* runner = u; runner; runner = runner->parent)
      {
        if (grid[runner->row][runner->col] == '.')
          grid[runner->row][runner->col] = '*';
        if (animate)
        {
          maze->draw();
          usleep(DRAW_DELAY);
        }
      }

      delete u;
      while(!frontier.empty())
      {
        u = frontier.back(); frontier.pop_back();
        delete u;
      }
      while (!to_delete.empty())
      {
        u = to_delete.back(); to_delete.pop_back();
        delete u;
      }

      if (animate)
      {
        getchar();
        endwin();
      }
      return;
    }

    if (grid[u->row][u->col] != 'S')
      grid[u->row][u->col] = '.';
    std::vector<Cell> neighbors = get_neighbors(u, maze->get_rows(), maze->get_cols());
    for (size_t i = 0; i < neighbors.size(); i++)
    {
      switch (grid[neighbors[i].row][neighbors[i].col])
      {
        case '.':
        case '#':
        case ',':
        case 'S':
          continue;
      }
      if (grid[neighbors[i].row][neighbors[i].col] != 'E')
        grid[neighbors[i].row][neighbors[i].col] = ',';
      if (animate)
      {
        maze->draw();
        usleep(DRAW_DELAY);
      }
      neighbors[i].parent = u;
      Cell* v = new Cell;
      *v = neighbors[i];
      frontier.push_back(v);
    }

    if (u->parent != NULL)
      to_delete.push_back(u);
  }

  if (animate)
  {
    getchar();
    endwin();
  }

  return;
}

std::vector<Cell> get_neighbors(Cell* cell, const int max_row, const int max_col)
{
  std::vector<Cell> neighbors;
  Cell new_cell;
  int new_row;
  int new_col;
  int offset[4][2] = {{-1, 0},
    {0, +1},
    {+1, 0},
    {0, -1}};

  for (int i = 0; i < 4; i++)
  {
    new_row = cell->row + offset[i][0];
    new_col = cell->col + offset[i][1];
    if (new_row >= 0 && new_col >= 0 &&
        new_row < max_row && new_col < max_col)
    {
      new_cell.row = new_row;
      new_cell.col = new_col;
      neighbors.push_back(new_cell);
    }
  }

  return neighbors;
}

void Solver::player_control()
{
  Player* player = new Player(maze, 0, 0);
  bool done = false;

  maze->init_curses();
  maze->draw();

  int c;
  while (!done)
  {
    c = wgetch(stdscr);
    switch (c)
    {
      case KEY_UP:
        player->move(UP);
        break;
      case KEY_DOWN:
        player->move(DOWN);
        break;
      case KEY_LEFT:
        player->move(LEFT);
        break;
      case KEY_RIGHT:
        player->move(RIGHT);
        break;
    }
    maze->draw();

    if (player->game_won)
    {
      clear();
      mvwprintw(stdscr, maze->get_cols() / 2, maze->get_rows() / 2, "You win!");
      done = true;
    }
  }
  delete player;
  getch();
  endwin();
  return;
}
