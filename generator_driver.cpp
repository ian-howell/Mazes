#include <cstdio>
#include <ncurses.h>
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include "maze.h"
#include "generator.h"
#include <string>

int main(int argc, char** argv)
{
  int rows = -1;
  int cols = -1;
  char* algorithm = NULL;
  char* output_file = NULL;
  bool animate_flag = false;

  int c;
  int opt_index = 0;
  struct option opts[] = {
    {"rows",         required_argument, 0, 'r'},
    {"cols",         required_argument, 0, 'c'},
    {"algorithm",    required_argument, 0, 'a'},
    {"animate",      no_argument,       0, 0},
    {"file",         required_argument, 0, 'f'},
    {"speed",        required_argument, 0, 's'}
  };

  while ((c = getopt_long(argc, argv, "r:c:a:f:s:h", opts, &opt_index)) != -1)
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
      case 'f':
        output_file = optarg;
        break;
      case 's':
        Maze::draw_delay = 1000 * std::stoi(optarg);
        break;
      case 0:
        animate_flag = true;
        break;
    }
  }

  if (!algorithm)
  {
    fprintf(stderr, "Must specify an algorithm (prims)\n");
    return 0;
  }

  // Get the screen dimensions (in case the user didn't enter any)
  if (rows < 0 || cols < 0)
  {
    int max_rows, max_cols;
    initscr();
    getmaxyx(stdscr, max_rows, max_cols);
    endwin();

    // Normalize the dimensions so there is a border between the edge of
    // the screen and the maze walls
    rows = (rows < 0) ? max_rows - 2 : rows;
    cols = (cols < 0) ? max_cols - 2 : cols;
  }


  std::shared_ptr<Generator> generator(new Generator(rows, cols));
  MazePtr maze = generator->prims(animate_flag);
  if (output_file)
    maze->print(output_file);

  return 0;
}
