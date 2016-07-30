#include "maze.h"
#include <stdio.h>
#include <ncurses.h>
#include <cstdlib>

int main(int argc, char** argv)
{
    Maze *maze = NULL;
    if (argc == 3)
    {
        maze = new Maze(atoi(argv[1]), atoi(argv[2]));
    }
    else
    {
        initscr();
        maze = new Maze();
        getch();
        // Close ncurses
        endwin();
    }

    maze->print();


    delete maze;

    return 0;
}
