#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stack>

#include "cell.h"
#include "maze.h"
#include "generator.h"
#include "union_find.h"

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
  finished(maze, animate);
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
  finished(maze, animate);
  maze->maybe_endwin(animate);

  return maze;
}

MazePtr Generator::kruskal(bool animate)
{
  MazePtr maze(new Maze(rows, cols));
  maze->maybe_init(animate);

  // Add all the edges to a list
  std::vector<CellPtr> nodes;
  int count = 0;
  for (int i = 0; i < rows; i += 2)
  {
    for (int j = 0; j < cols; j += 2)
    {
      nodes.push_back(CellPtr(new Cell(i, j, NULL)));
    }
  }

  int node_rows = rows / 2 + 1;
  int node_cols = cols / 2 + 1;

  // Add all the edges
  using edge_t = std::pair<int, int>;
  std::vector<edge_t> edges;
  for (int r = 0; r < node_rows; r++)
  {
    for (int c = 0; c < node_cols; c++)
    {
      int this_cell = c + (r*node_cols);
      int right_cell = (c+1) + (r*node_cols);
      int lower_cell = c + ((r+1)*node_cols);

      if (nodes[this_cell]->col != cols-1)
        edges.push_back(std::make_pair(this_cell, right_cell));
      if (nodes[this_cell]->row != rows-1)
        edges.push_back(std::make_pair(this_cell, lower_cell));
    }
  }

  // Make each node a set containing only itself
  int num_nodes = nodes.size();
  std::vector<UnionFindSet> sets;
  for (int i = 0; i < num_nodes; i++)
    sets.push_back(UnionFindSet(i));

  int total_edges = 0;
  while (total_edges < num_nodes-1)
  {
    // Get a random edge from the list of edges
    int rand_point = rand() % edges.size();
    edge_t next_edge = edges[rand_point];
    edges.erase(edges.begin() + rand_point);

    // Find the representative of the set of each node for this edge
    int x = find(sets, next_edge.first);
    int y = find(sets, next_edge.second);

    // If the nodes are not in the same set, join them
    if (x != y)
    {
      int first_row = nodes[next_edge.first]->row;
      int first_col = nodes[next_edge.first]->col;
      int second_row = nodes[next_edge.second]->row;
      int second_col = nodes[next_edge.second]->col;
      int mid_row = (first_row + second_row) / 2;
      int mid_col = (first_col + second_col) / 2;

      maze->at(first_row, first_col) = 'E';
      maze->at(second_row, second_col) = 'E';
      maze->at(mid_row, mid_col) = 'E';
      maze->maybe_draw(animate);
      maze->at(first_row, first_col) = ' ';
      maze->at(second_row, second_col) = ' ';
      maze->at(mid_row, mid_col) = ' ';
      join(sets, x, y);
      total_edges++;
    }
  }

  maze->at(0, 0) = 'S';
  maze->at(rows - 1, cols - 1) = 'E';
  maze->maybe_draw(animate);
  finished(maze, animate);
  maze->maybe_endwin(animate);

  return maze;
}

void Generator::finished(MazePtr maze, bool animate)
{
  if (animate)
  {
    const char* msg = "Finished generation. Press any key to continue...";
    maze->maybe_message(msg);
    getch();
  }
  return;
}
