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
  maybe_init(animate);
  ret_val = backtrack_r(start, animate);
  maybe_endwin(animate);
  return ret_val;
}

bool Solver::backtrack_r(Cell cell, bool animate)
{
  std::vector<Cell> neighbors = maze->get_neighbors(&cell);
  for (size_t i = 0; i < neighbors.size(); i++)
  {
    int row = neighbors[i].row;
    int col = neighbors[i].col;

    if (grid[row][col] == 'E')
    {
      return true;
    }

    grid[row][col] = '*';

    maybe_draw(animate);

    grid[row][col] = '.';

    if (backtrack_r(neighbors[i], animate))
    {
      grid[row][col] = '*';

      maybe_draw(animate);
      return true;
    }
    else
    {
      grid[row][col] = '*';

      maybe_draw(animate);
      grid[row][col] = ' ';
    }
  }
  return false;
}

void Solver::X_first_search(SOLVE_TYPE solve_type, bool animate)
{
  std::deque<Cell*> frontier;
  std::deque<Cell*> to_delete;

  maybe_init(animate);
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
        maybe_draw(animate);
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

      maybe_endwin(animate);
      return;
    }

    if (grid[u->row][u->col] != 'S')
      grid[u->row][u->col] = '.';
    std::vector<Cell> neighbors = maze->get_neighbors(u);
    for (size_t i = 0; i < neighbors.size(); i++)
    {
      if (grid[neighbors[i].row][neighbors[i].col] != 'E')
        grid[neighbors[i].row][neighbors[i].col] = ',';
      maybe_draw(animate);
      neighbors[i].parent = u;
      Cell* v = new Cell;
      *v = neighbors[i];
      frontier.push_back(v);
    }

    if (u->parent != NULL)
      to_delete.push_back(u);
  }

  maybe_endwin(animate);
  return;
}

void Solver::player_control()
{
  Player* player = new Player(maze, 0, 0);
  bool done = false;

  maybe_init();

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
  maybe_endwin();
  return;
}

void Solver::maybe_init(bool animate)
{
  if (animate)
  {
    maze->init_curses();
    maze->draw();
  }
  return;
}

void Solver::maybe_endwin(bool animate)
{
  if (animate)
  {
    getch();
    endwin();
  }
  return;
}

void Solver::maybe_draw(bool animate)
{
  if (animate)
  {
    maze->draw();
    usleep(DRAW_DELAY);
  }
  return;
}
