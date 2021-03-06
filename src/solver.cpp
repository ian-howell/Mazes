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

Solver::Solver(bool diag) :
  allow_diag(diag)
{
  /* Intentionally left empty */
}

void Solver::solve(MazePtr maze, solve_t algorithm, bool animate)
{
  maze->init_curses();
  switch(algorithm)
  {
    case BFS:
    case DFS:
      X_first_search(maze, algorithm);
      break;
    case BACKTRACKING:
      backtrack(maze);
      break;
    case ASTAR:
      astar(maze);
      break;
    case PLAY:
      player_control(maze);
      break;
  }
  if (algorithm != PLAY)
    mouse_control(maze, algorithm, animate);
  maze->end_curses();
  return;
}

bool Solver::backtrack(MazePtr maze)
{
  return backtrack_r(maze, maze->get_start());
}

bool Solver::backtrack_r(MazePtr maze, CellPtr cell)
{
  if (*cell == *maze->get_end())
    return true;

  std::vector<CellPtr> neighbors = maze->get_neighbors(cell, Maze::FLOOR, allow_diag);
  for (size_t i = 0; i < neighbors.size(); i++)
  {
    int row = neighbors[i]->row;
    int col = neighbors[i]->col;
    if (*neighbors[i] == *maze->get_end())
      return true;

    maze->at(row, col) = ',';
    maze->draw(Maze::draw_delay);
    maze->at(row, col) = '.';

    if (backtrack_r(maze, neighbors[i]))
    {
      maze->at(row, col) = '*';
      maze->draw(Maze::draw_delay);
      return true;
    }
    else
    {
      maze->at(row, col) = ',';
      maze->draw(Maze::draw_delay);
      maze->at(row, col) = ' ';
    }
  }
  return false;
}

bool Solver::X_first_search(MazePtr maze, solve_t solve_type)
{
  std::deque<CellPtr> frontier;

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
        maze->draw(Maze::draw_delay);
      }

      return true;
    }

    if (maze->at(u->row, u->col) != 'S')
      maze->at(u->row, u->col) = '.';
    std::vector<CellPtr> neighbors = maze->get_neighbors(u, Maze::FLOOR, allow_diag);
    for (size_t i = 0; i < neighbors.size(); i++)
    {
      if (maze->at(neighbors[i]->row, neighbors[i]->col) != 'E')
        maze->at(neighbors[i]->row, neighbors[i]->col) = ',';
      maze->draw(Maze::draw_delay);
      frontier.push_back(CellPtr(neighbors[i]));
    }
  }

  // No path was found
  return false;
}

void Solver::player_control(MazePtr maze)
{
  Player* player = new Player(0, 0);
  bool done = false;
  maze->draw();

  int c;
  while (!done)
  {
    maze->message("Move with the arrow keys, or press q to quit");
    c = wgetch(stdscr);
    if (c == KEY_UP)
      done = player->move(maze, Player::UP);
    else if (c == KEY_DOWN)
      done = player->move(maze, Player::DOWN);
    else if (c == KEY_LEFT)
      done = player->move(maze, Player::LEFT);
    else if (c == KEY_RIGHT)
      done = player->move(maze, Player::RIGHT);
    else if (c == 'q')
      done = true;
    maze->draw();
  }
  if (done)
    maze->message("Success!");
  delete player;
  return;
}

bool Solver::astar(MazePtr maze)
{
  // Describe a pair (for the comparison function)
  using my_pair_t = std::pair<CellPtr, double>;
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
  using cell_map_t = std::map<int, double>;
  cell_map_t cost_so_far;

  // Add the current cost to get to the start to the list of current costs
  cost_so_far[maze->get_index(maze->get_start())] = 0;

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
          maze->draw(Maze::draw_delay);
        }
      }

      return true;
    }

    if (maze->at(current_node.first->row, current_node.first->col) != 'S')
    {
      maze->at(current_node.first->row, current_node.first->col) = '.';
      maze->draw(Maze::draw_delay);
    }

    std::vector<CellPtr> neighbors = maze->get_neighbors(current_node.first,
        Maze::FLOOR, allow_diag);
    for (int i = 0; i < neighbors.size(); i++)
    {
      bool different_row = (current_node.first->row != neighbors[i]->row);
      bool different_col = (current_node.first->col != neighbors[i]->col);
      double new_cost;
      if (different_row && different_col) // diagonal
        new_cost = cost_so_far[maze->get_index(current_node.first)] + 1.4;
      else
        new_cost = cost_so_far[maze->get_index(current_node.first)] + 1;

      // If we haven't visited this node, or the new cost is better, add it
      int neighbor_idx = maze->get_index(neighbors[i]);
      if (!cost_so_far.count(neighbor_idx) || new_cost < cost_so_far[neighbor_idx])
      {
        int distance = manhattan_distance(neighbors[i], maze->get_end());
        /* int distance = real_distance(current_node.first, neighbors[i]); */
        frontier.push(std::make_pair(neighbors[i], distance + new_cost));
        cost_so_far[neighbor_idx] = new_cost;

        if (maze->at(neighbors[i]->row, neighbors[i]->col) != 'E')
        {
          maze->at(neighbors[i]->row, neighbors[i]->col) = ',';
          maze->draw(Maze::draw_delay);
        }
      }
    }
  }
  return false;
}

double Solver::manhattan_distance(CellPtr first, CellPtr second)
{
  // on macOS, g++ and clang++ gets very confused when you're trying
  // to use std::abs when also including cmath.
  // see here: http://stackoverflow.com/questions/1374037/ambiguous-overload-call-to-absdouble
  double drow = std::abs(static_cast<double>(first->row - second->row));
  double dcol = std::abs(static_cast<double>(first->col - second->col));
  return (drow + dcol);
}

double Solver::real_distance(CellPtr first, CellPtr second)
{
  // If you're wondering why the `static_cast`, read the
  // manhattan_distance method
  double drow = std::abs(static_cast<double>(first->row - second->row));
  double dcol = std::abs(static_cast<double>(first->col - second->col));
  return std::sqrt(std::pow(drow, 2) + std::pow(dcol, 2));
}

void Solver::mouse_control(MazePtr maze, solve_t algorithm, bool animate)
{
  // Only run this function if ncurses is running
  if (!animate)
    return;

  maze->init_curses();

  maze->draw();
  const char* msg = "Click to move start, ctrl-click to move finish, "
    "or press any other key to end";
  maze->message(msg);

  int row;
  int col;
  bool done = false;
  MEVENT event;
  while ((!done) && (getch() == KEY_MOUSE) && (getmouse(&event) == OK))
  {
    row = event.y-1;
    col = event.x-1;

    // Remove the detritus from the maze before checking if this space is valid
    // Note that this call will not display the cleared maze
    maze->clear();
    if (maze->is_pathable(row, col))
    {
      if (event.bstate == BUTTON1_CLICKED)
      {
        // Move the start cell
        maze->set_start(row, col);
        // Need to redraw where the end is incase it has been overwritten
        maze->set_end(maze->get_end()->row, maze->get_end()->col);
      }
      else if (event.bstate == (BUTTON1_CLICKED | BUTTON_CTRL))
      {
        // Move the end cell
        maze->set_end(row, col);
        // Need to redraw where the start is incase it has been overwritten
        maze->set_start(maze->get_start()->row, maze->get_start()->col);
      }
      done = true;
      solve(maze, algorithm);
    }
  }

  maze->end_curses();
  return;
}
