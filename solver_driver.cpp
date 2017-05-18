#include <cstdio>
#include <ncurses.h>
#include <getopt.h>
#include <cstring>
#include <iostream>
#include "maze.h"
#include "solver.h"

int main(int argc, char** argv)
{
  int c;
  int opt_index = 0;
  char* algorithm = NULL;
  char* input_file = NULL;
  char* output_file = NULL;
  bool animate_flag = false;
  bool diag_flag = false;

  struct option opts[] = {
    {"algorithm",    required_argument, 0, 'a'},
    {"infile",       required_argument, 0, 'i'},
    {"outfile",      required_argument, 0, 'o'},
    {"animate",      no_argument,       0, 0},
    {"speed",        required_argument, 0, 's'},
    {"diag",         no_argument,       0, 'd'}
  };

  while ((c = getopt_long(argc, argv, "a:i:o:s:h", opts, &opt_index)) != -1)
  {
    switch (c)
    {
      case 'a':
        algorithm = optarg;
        break;
      case 'i':
        input_file = optarg;
        break;
      case 'o':
        output_file = optarg;
        break;
      case 's':
        Maze::draw_delay = 1000 * std::stoi(optarg);
        break;
      case 'd':
        diag_flag = true;
        break;
      case 0:
        animate_flag = true;
        break;
    }
  }

  if (!algorithm || !input_file)
  {
    fprintf(stderr, "Both an algorithm and an input file are required\n");
    return 0;
  }

  MazePtr maze(new Maze(input_file, animate_flag));
  std::shared_ptr<Solver> solver(new Solver(diag_flag));
  Solver::solve_t solve_type = Solver::BACKTRACKING;

  if (strcmp(algorithm, "bt") == 0)
    solve_type = Solver::BACKTRACKING;
  else if (strcmp(algorithm, "bfs") == 0)
    solve_type = Solver::BFS;
  else if (strcmp(algorithm, "dfs") == 0)
    solve_type = Solver::DFS;
  else if (strcmp(algorithm, "astar") == 0)
    solve_type = Solver::ASTAR;
  else if (strcmp(algorithm, "play") == 0)
    solve_type = Solver::PLAY;

  solver->mouse_control(maze, solve_type, animate_flag);

  if (output_file)
    maze->print(output_file);

  return 0;
}
