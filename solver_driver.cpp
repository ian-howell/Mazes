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
  int c;
  int opt_index = 0;
  char* algorithm = NULL;
  char* input_file = NULL;

  struct option opts[] = {
    {"algorithm",    required_argument, 0, 'a'},
    {"file",         required_argument, 0, 'f'}
  };

  while ((c = getopt_long(argc, argv, "r:c:a:h", opts, &opt_index)) != -1)
  {
    switch (c)
    {
      case 'a':
        algorithm = optarg;
        break;
      case 'f':
        input_file = optarg;
        break;
    }
  }

  if (!algorithm || !input_file)
  {
    fprintf(stderr, "Both an algorithm and an input file are required\n");
    return 0;
  }

  Maze* maze = new Maze(input_file);
  maze->print("out.txt");

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

  delete maze;
  /* delete solver; */
  /* delete player; */

  return 0;
}
