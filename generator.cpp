#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stack>

#include "cell.h"
#include "maze.h"
#include "generator.h"

Generator::Generator(int r, int c)
{
  rows = (r % 2) ? r : r - 1;
  cols = (c % 2) ? c : c - 1;
  srand(time(NULL));
}

MazePtr Generator::prims(bool animate)
{
  MazePtr maze(new Maze(rows, cols));
  maze->maybe_init(animate);

  CellPtr start(new Cell(0, 0, NULL));
  maze->at(start->row, start->col) = 'S';

  std::vector<CellPtr> frontier;
  // Add the start node's neighbors to the frontier
  frontier.push_back(CellPtr(new Cell(1, 0, start)));
  frontier.push_back(CellPtr(new Cell(0, 1, start)));

  CellPtr child;
  CellPtr gc;
  while (!frontier.empty())
  {
    int rand_point = rand() % frontier.size();
    child = frontier[rand_point];
    frontier.erase(frontier.begin() + rand_point);

    gc = child->get_child();
    int r = gc->row;
    int c = gc->col;

    if (maze->is_valid(r, c) && maze->at(r, c) == '#')
    {
      maze->at(child->row, child->col) = ' ';
      maze->at(r, c) = 'E';

      std::vector<CellPtr> neighbors = maze->get_neighbors(gc, true);
      for (int i = 0; i < neighbors.size(); i++)
        frontier.push_back(neighbors[i]);

      maze->maybe_draw(animate);
      maze->at(r, c) = ' ';
    }
  }

  maze->at(rows - 1, cols - 1) = 'E';
  maze->maybe_draw(animate);
  maze->maybe_endwin(animate);

  return maze;
}

MazePtr Generator::dfs(bool animate)
{
  MazePtr maze(new Maze(rows, cols));
  maze->maybe_init(animate);

  CellPtr start(new Cell(0, 0, NULL));
  maze->at(start->row, start->col) = 'S';
  maze->maybe_draw(animate);

  std::stack<CellPtr> frontier;
  // Add the start node's neighbors to the frontier (in random order)
  std::vector<CellPtr> neighbors = maze->get_neighbors(start, true);
  while (neighbors.size() > 0)
  {
    int rand_point = rand() % neighbors.size();
    frontier.push(neighbors[rand_point]);
    neighbors.erase(neighbors.begin() + rand_point);
  }

  while (!frontier.empty())
  {
    CellPtr child = frontier.top();
    frontier.pop();

    CellPtr gc = child->get_child();
    int r = gc->row;
    int c = gc->col;

    if (maze->is_valid(r, c) && maze->at(r, c) == '#')
    {
      maze->at(child->row, child->col) = ' ';
      maze->at(r, c) = 'E';
      maze->maybe_draw(animate);
      maze->at(r, c) = ' ';

      std::vector<CellPtr> neighbors = maze->get_neighbors(gc, true);
      while (neighbors.size() > 0)
      {
        int rand_point = rand() % neighbors.size();
        frontier.push(neighbors[rand_point]);
        neighbors.erase(neighbors.begin() + rand_point);
      }
    }
  }
  maze->at(rows - 1, cols - 1) = 'E';
  maze->maybe_draw(animate);
  maze->maybe_endwin(animate);

  return maze;
}
