#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include "maze.h"

void usage(const char* prgname);

int main(int argc, char** argv)
{
    int myarg;
    int rows = 10;
    int cols = 10;
    bool animate_flag = false;;
    bool print_unsolved = false;

    initscr();
    getmaxyx(stdscr, rows, cols);
    printf("row: %d\ncols: %d\n", rows, cols);
    while ((myarg = getopt(argc, argv, "c:r:ahus")) != -1)
    {
        switch (myarg)
        {
            case 'r':
                rows = atoi(optarg);
                break;
            case 'c':
                cols = atoi(optarg);
                break;
            case 'a':
                animate_flag = true;
                break;
            case 'u':
                print_unsolved = true;
                break;
            case 'h':
                usage(argv[0]);
                endwin();
                return 0;
        }
    }

    Maze *maze = new Maze(rows, cols, animate_flag);

    if (animate_flag)
        getch();

    endwin();

    setvbuf(stdout, NULL, _IONBF, 0);

    if (print_unsolved)
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
