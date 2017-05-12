#include <cstdio>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <getopt.h>
#include "maze.h"
#include "solver.h"
#include "player.h"
#include "generator.h"

int main(int argc, char** argv)
{
  int rows = 10;
  int cols = 10;
  std::string algorithm = "nothing";
  bool animate_flag = false;

  // Get the screen dimensions
  initscr();
  getmaxyx(stdscr, rows, cols);
  endwin();

  // Normalize the dimensions so there is a border between the edge of
  // the screen and the maze walls
  rows -= 2;
  cols -= 2;

  int c;
  int opt_index = 0;
  struct option opts[] = {
    {"rows",         required_argument, 0, 'r'},
    {"cols",         required_argument, 0, 'c'},
    {"algorithm",    required_argument, 0, 'a'},
    {"animate",      no_argument,       0, 0}
  };

  while ((c = getopt_long(argc, argv, "r:c:a:h", opts, &opt_index)) != -1)
  {
    switch (c)
    {
      case 'r':
        rows = atoi(optarg);
        break;
      case 'c':
        cols = atoi(optarg);
        break;
      case 'a':
        algorithm = optarg;
        break;
      case 0:
        animate_flag = true;
        break;
    }
  }

  Maze* maze = new Maze(rows, cols);
  Generator* generator = new Generator(maze);
  generator->create_maze(animate_flag);
  maze->print();

  delete maze;
  delete generator;

  return 0;
}
