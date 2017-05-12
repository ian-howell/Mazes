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

void usage(const char* prgname);

int main(int argc, char** argv)
{
  int myarg;
  int rows = 10;
  int cols = 10;
  int flags;

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

  std::string algorithm = "nothing";

  struct option opts[] = {
    {"rows",         required_argument, 0, 'r'},
    {"cols",         required_argument, 0, 'c'},
    {"algorithm",    required_argument, 0, 'a'}
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
      case 'h':
        usage(argv[0]);
        return 0;
    }
  }

  Maze* maze = new Maze(rows, cols);
  Generator* generator = new Generator(maze);
  generator->create_maze(false);
  maze->print();

  /* Solver* solver = new Solver(maze, ANIMATE_SOLVE); */
  /* Player* player = new Player(maze, 0, 0); */

  /* if (MAN_SOLVE) */
  /* { */
  /*     start_color(); */
  /*     noecho(); */
  /*     cbreak(); */

  /*     refresh(); */

  /*     maze->draw(); */

  /*     int c; */

  /*     while (1) */
  /*     { */
  /*         c = wgetch(stdscr); */
  /*         switch (c) */
  /*         { */
  /*             case KEY_UP: */
  /*                 player->move(UP); */
  /*                 break; */
  /*             case KEY_DOWN: */
  /*                 player->move(DOWN); */
  /*                 break; */
  /*             case KEY_LEFT: */
  /*                 player->move(LEFT); */
  /*                 break; */
  /*             case KEY_RIGHT: */
  /*                 player->move(RIGHT); */
  /*                 break; */
  /*         } */
  /*         /1* player->draw(); *1/ */
  /*         maze->draw(); */

  /*         if (player->game_won) */
  /*         { */
  /*             clear(); */
  /*             mvwprintw(stdscr, cols / 2, rows / 2, "You win!"); */
  /*             break; */
  /*         } */
  /*     } */
  /* } */
  /* else if (BACKTRACK_SOLVE) */
  /* { */
  /*     maze->draw(); */
  /*     solver->backtrack(); */
  /* } */
  /* else if (BFS_SOLVE) */
  /* { */
  /*     maze->draw(); */
  /*     solver->breadth_first_search(); */
  /* } */

  /* getch(); */

  endwin();

  /* if (PRINT_SOLVED) */
  /*     maze->print(); */

  delete maze;
  delete generator;
  /* delete solver; */
  /* delete player; */

  return 0;
}

void usage(const char* prgname)
{
  printf("Usage: %s [OPTION]...\n", prgname);
  printf("Example: %s -r 10 -c 15 -usa\n", prgname);
  printf("%-20s", "  -r NUM");
  printf("%-30s\n", "Maze will have NUM rows");
  printf("%-20s", "  -c NUM");
  printf("%-30s\n", "Maze will have NUM columnsrows");
  printf("%-20s", "  -a");
  printf("%-30s\n", "Animate maze with ncurses");
  printf("%-20s", "  -u");
  printf("%-30s\n", "Print resulting unsolved maze");
  printf("%-20s", "  -s");
  printf("%-30s\n", "Print resulting solved maze");
  printf("%-20s", "  -h");
  printf("%-30s\n", "Show this help message");
}
