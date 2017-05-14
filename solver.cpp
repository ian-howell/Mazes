#include <unistd.h>
#include "solver.h"
#include "cell.h"
#include "maze.h"
#include "player.h"
#include <cstdio>
#include <ncurses.h>
#include <vector>
#include <deque>

Solver::Solver()
{
  /* Intentionally left empty */
}

bool Solver::backtrack(MazePtr maze, bool animate)
{
  bool ret_val;
  maze->maybe_init(animate);
  ret_val = backtrack_r(maze, maze->get_start(), animate);
  maze->maybe_endwin(animate);
  return ret_val;
}

bool Solver::backtrack_r(MazePtr maze, CellPtr cell, bool animate)
{
  std::vector<CellPtr> neighbors = maze->get_neighbors(cell);
  for (size_t i = 0; i < neighbors.size(); i++)
  {
    int row = neighbors[i]->row;
    int col = neighbors[i]->col;
    if (*neighbors[i] == *maze->get_end())
      return true;

    maze->at(row, col) = '*';
    maze->maybe_draw(animate);
    maze->at(row, col) = '.';

    if (backtrack_r(maze, neighbors[i], animate))
    {
      maze->at(row, col) = '*';
      maze->maybe_draw(animate);
      return true;
    }
    else
    {
      maze->at(row, col) = '*';
      maze->maybe_draw(animate);
      maze->at(row, col) = ' ';
    }
  }
  return false;
}

void Solver::X_first_search(MazePtr maze, SOLVE_TYPE solve_type, bool animate)
{
  std::deque<CellPtr> frontier;

  maze->maybe_init(animate);
  CellPtr start = maze->get_start();
  frontier.push_back(CellPtr(start));

  CellPtr u;
  while (!frontier.empty())
  {
    if (solve_type == BFS)
    {
      u = frontier.front();
      frontier.pop_front();
    }
    else if (solve_type == DFS)
    {
      u = frontier.back();
      frontier.pop_back();
    }

    if (*u == *maze->get_end())
    {
      for (CellPtr r = u; r; r = r->parent)
      {
        if (maze->at(r->row, r->col) == '.')
          maze->at(r->row, r->col) = '*';
        maze->maybe_draw(animate);
      }

      maze->maybe_endwin(animate);
      return;
    }

    if (maze->at(u->row, u->col) != 'S')
      maze->at(u->row, u->col) = '.';
    std::vector<CellPtr> neighbors = maze->get_neighbors(u);
    for (size_t i = 0; i < neighbors.size(); i++)
    {
      if (maze->at(neighbors[i]->row, neighbors[i]->col) != 'E')
        maze->at(neighbors[i]->row, neighbors[i]->col) = ',';
      maze->maybe_draw(animate);
      neighbors[i]->parent = u;
      frontier.push_back(CellPtr(neighbors[i]));
    }
  }

  maze->maybe_endwin(animate);
  return;
}

void Solver::player_control(MazePtr maze)
{
  Player* player = new Player(0, 0);
  bool done = false;
  maze->maybe_init();

  int c;
  while (!done)
  {
    c = wgetch(stdscr);
    if (c == KEY_UP)
      done = player->move(maze, Player::UP);
    else if (c == KEY_DOWN)
      done = player->move(maze, Player::DOWN);
    else if (c == KEY_LEFT)
      done = player->move(maze, Player::LEFT);
    else if (c == KEY_RIGHT)
      done = player->move(maze, Player::RIGHT);
    maze->draw();
  }
  delete player;
  maze->maybe_endwin();
  return;
}
