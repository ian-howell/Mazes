#include <cstdio>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include "maze.h"
#include "solver.h"
#include "player.h"

void usage(const char* prgname);

int main(int argc, char** argv)
{
    int myarg;
    int rows = 10;
    int cols = 10;
    bool animate_flag = false;;
    bool print_unsolved = false;
    bool print_solved = false;
    bool play_flag = false;

    initscr();
    getmaxyx(stdscr, rows, cols);
    while ((myarg = getopt(argc, argv, "c:r:ahusp")) != -1)
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
            case 's':
                print_solved = true;
                break;
            case 'h':
                endwin();
                usage(argv[0]);
                return 0;
            case 'p':
                play_flag = true;
                break;
        }
    }

    if (!print_solved && !print_unsolved && !animate_flag)
    {
        endwin();
        usage(argv[0]);
        return 0;
    }

    Maze *maze = new Maze(rows, cols, animate_flag);

    if (print_unsolved)
    {
        endwin();
        maze->print();
        initscr();
    }

    Solver* solver = new Solver(animate_flag);
    Player* player = new Player(maze, 0, 0);

    if (play_flag)
    {
        start_color();
        noecho();
        cbreak();

        keypad(stdscr, TRUE);

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
    else
    {
        solver->solve(maze);
    }

    if (animate_flag)
        getch();

    endwin();

    if (print_solved)
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
