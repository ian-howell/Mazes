#include <unistd.h>
#include "solver.h"
#include "cell.h"
#include "maze.h"
#include "player.h"
#include <cstdio>
#include <ncurses.h>
#include <vector>
#include <deque>
#include <queue>
#include <utility>
#include <map>
#include <cmath>

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

bool Solver::astar(MazePtr maze, bool animate)
{
  maze->maybe_init(animate);

  // Describe a pair (for the comparison function)
  using my_pair_t = std::pair<CellPtr, int>;
  // Comparison function
  auto cmp = [] (const my_pair_t& left, const my_pair_t& right)
  {return left.second > right.second;};
  // Describe a priority queue using the comparison function
  using pqueue_t = std::priority_queue<my_pair_t, std::vector<my_pair_t>,
        decltype(cmp)>;
  pqueue_t frontier(cmp);

  // Add the start node to the pqueue
  frontier.push(std::make_pair(maze->get_start(), 0));

  // Keep track of the cost to a given node at any given time
  using cell_map_t = std::map<CellPtr, int>;
  cell_map_t cost_so_far;

  // Add the current cost to get to the start to the list of current costs
  cost_so_far[maze->get_start()] = 0;

  while (!frontier.empty())
  {
    // Get the lowest priority node from the pqueue
    my_pair_t current_node = frontier.top();
    frontier.pop();

    // Check to see if we're at the end
    if (*current_node.first == *maze->get_end())
    {
      for (CellPtr r = current_node.first; r; r = r->parent)
      {
        if (maze->at(r->row, r->col) == '.')
        {
          maze->at(r->row, r->col) = '*';
          maze->maybe_draw(animate);
        }
      }

      maze->maybe_endwin(animate);
      return true;
    }

    if (maze->at(current_node.first->row, current_node.first->col) != 'S')
    {
      maze->at(current_node.first->row, current_node.first->col) = '.';
      maze->maybe_draw(animate);
    }

    std::vector<CellPtr> neighbors = maze->get_neighbors(current_node.first);
    for (int i = 0; i < neighbors.size(); i++)
    {
      // Path cost = 1
      int new_cost = cost_so_far[current_node.first] + 1;

      // If we haven't visited this node, or the new cost is better, add it
      if (!cost_so_far.count(neighbors[i]) || new_cost < cost_so_far[neighbors[i]])
      {
        int distance = manhattan_distance(neighbors[i], maze->get_end());
        /* int distance = real_distance(current_node.first, neighbors[i]); */
        frontier.push(std::make_pair(neighbors[i], distance));
        cost_so_far[neighbors[i]] = new_cost;

        if (maze->at(neighbors[i]->row, neighbors[i]->col) != 'E')
        {
          maze->at(neighbors[i]->row, neighbors[i]->col) = ',';
          maze->maybe_draw(animate);
        }
      }
    }
  }
  maze->maybe_endwin(animate);
  return false;
}

int Solver::manhattan_distance(CellPtr first, CellPtr second)
{
  // on macOS, g++ and clang++ gets very confused when you're trying
  // to use std::abs when also including cmath.
  // see here: http://stackoverflow.com/questions/1374037/ambiguous-overload-call-to-absdouble
  int drow = std::abs(static_cast<float>(first->row - second->row));
  int dcol = std::abs(static_cast<float>(first->col - second->col));
  return (drow + dcol);
}

int Solver::real_distance(CellPtr first, CellPtr second)
{
  // If you're wondering why the `static_cast`, read the
  // manhattan_distance method
  int drow = std::abs(static_cast<float>(first->row - second->row));
  int dcol = std::abs(static_cast<float>(first->col - second->col));
  return std::sqrt(std::pow(drow, 2) + std::pow(dcol, 2));
}
