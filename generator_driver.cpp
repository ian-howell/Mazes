#include <cstdio>
#include <ncurses.h>
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include "maze.h"
#include "generator.h"

int main(int argc, char** argv)
{
  int rows = 10;
  int cols = 10;
  char* algorithm = NULL;
  char* output_file = NULL;
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
    {"animate",      no_argument,       0, 0},
    {"file",         required_argument, 0, 'f'}
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
      case 'f':
        output_file = optarg;
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

  std::shared_ptr<Generator> generator(new Generator(rows, cols));
  MazePtr maze = generator->create_maze(animate_flag);
  if (output_file)
    maze->print(output_file);

  printf("uses: %d\n", generator.use_count());
  return 0;
}
