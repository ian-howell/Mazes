#include <cstdio>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include "maze.h"
#include "solver.h"
#include "player.h"
#include "flags.h"
#include "mazemenu.h"

void usage(const char* prgname);

int main(int argc, char** argv)
{
    int myarg;
    int rows = 10;
    int cols = 10;
    int flags;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    getmaxyx(stdscr, rows, cols);
    while ((myarg = getopt(argc, argv, "c:r:h")) != -1)
    {
        switch (myarg)
        {
            case 'r':
                rows = atoi(optarg);
                break;
            case 'c':
                cols = atoi(optarg);
                break;
            case 'h':
                endwin();
                usage(argv[0]);
                return 0;
        }
    }

    flags = get_flags();

    Maze *maze = new Maze(rows, cols, ANIMATE);

    if (PRINT_UNSOLVED || PRINT_BOTH)
    {
        endwin();
        maze->print();
        initscr();
    }

    Solver* solver = new Solver(ANIMATE);
    Player* player = new Player(maze, 0, 0);

    if (MAN_SOLVE)
    {
        start_color();
        noecho();
        cbreak();

        refresh();
        int c;

        while (1)
        {
            c = wgetch(stdscr);
            switch (c)
            {
                case KEY_UP:
                    player->move(UP);
                    break;
                case KEY_DOWN:
                    player->move(DOWN);
                    break;
                case KEY_LEFT:
                    player->move(LEFT);
                    break;
                case KEY_RIGHT:
                    player->move(RIGHT);
                    break;
            }
            player->draw();

            if (player->game_won)
            {
                clear();
                mvwprintw(stdscr, cols / 2, rows / 2, "You win!");
                break;
            }
        }
    }
    else if (BACKTRACK_SOLVE)
    {
        solver->solve(maze);
    }

    endwin();

    if (PRINT_SOLVED || PRINT_BOTH)
        maze->print();

    delete maze;
    delete solver;
    delete player;

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
