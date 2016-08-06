#include "maze.h"
#include <stdio.h>
#include <ncurses.h>
#include <cstdlib>

void usage(const char* prgname);

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

void usage(const char* prgname)
{
    printf("Usage: %s [OPTION]...\n", prgname);
    printf("Example: %s -r 10 -c 15 -a\n", prgname);
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
