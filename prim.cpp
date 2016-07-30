#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <ncurses.h>
#include "cell.h"

bool is_valid(int r, int c, int max_row, int max_col);
char **generate_grid(int rows, int cols);

int main()
{
    int cols, rows;
    initscr();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_RED);

    getmaxyx(stdscr, rows, cols);
    if (cols % 2 == 0)
        cols -= 3;
    else
        cols -= 2;
    if (rows % 2 == 0)
        rows -= 3;
    else
        rows -= 2;

    /* rows = cols = 5; */

    srand(time(NULL));

    char **grid = generate_grid(rows, cols);

    Cell start(0, 0, NULL);
    grid[start.row][start.col] = 'S';

    std::vector<Cell *> frontier;

    // Add the start node's neighbors to the frontier
    frontier.push_back(new Cell(start.row + 1, start.col, &start));
    frontier.push_back(new Cell(start.row, start.col + 1, &start));

    Cell* child;
    Cell* gc;
    std::vector<Cell *> grandchildren;
    bool gc_used = false;

    while (!frontier.empty())
    {
        int rand_point = rand() % frontier.size();
        child = frontier[rand_point];
        frontier.erase(frontier.begin() + rand_point);

        gc = child->get_opposite();
        int r = gc->row;
        int c = gc->col;

        if (is_valid(r, c, rows, cols) && grid[r][c] == '#')
        {
            grid[child->row][child->col] = '.';
            grid[r][c] = '0';

            for (int i = -1; i <= 1; i += 2)
            {
                if (is_valid(r + i, c, rows, cols))
                {
                    frontier.push_back(new Cell(r + i, c, gc));
                    gc_used = true;
                }

                if (is_valid(r, c + i, rows, cols))
                {
                    frontier.push_back(new Cell(r, c + i, gc));
                    gc_used = true;
                }
            }

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (grid[i][j] == '#')
                        attron(COLOR_PAIR(1));
                    else if (grid[i][j] == '.')
                        attron(COLOR_PAIR(2));
                    else if (grid[i][j] == 'S')
                        attron(COLOR_PAIR(3));
                    else
                        attron(COLOR_PAIR(4));

                    mvwprintw(stdscr, i + 1, j + 1, " ");

                    attroff(COLOR_PAIR(1));
                    attroff(COLOR_PAIR(2));
                    attroff(COLOR_PAIR(3));
                    attroff(COLOR_PAIR(4));
                }
            }
            usleep(100000);
            refresh();
            grid[r][c] = '.';
        }

        delete child;

        if (!gc_used)
            delete gc;
        else
            grandchildren.push_back(gc);

    }

    /* for (int i = 0; i < cols + 2; i++) */
    /* { */
    /*     printf("#"); */
    /* } */
    /* printf("\n"); */

    /* for (int i = 0; i < rows; i++) */
    /* { */
    /*     printf("#"); */
    /*     for (int j = 0; j < cols; j++) */
    /*     { */
    /*         printf("%c", grid[i][j]); */
    /*     } */
    /*     printf("#\n"); */
    /* } */

    /* for (int i = 0; i < cols + 2; i++) */
    /* { */
    /*     printf("#"); */
    /* } */
    /* printf("\n"); */

    for (int i = 0; i < rows; i++)
    {
        delete [] grid[i];
    }
    delete [] grid;

    for (int i = 0; i < (int)grandchildren.size(); i++)
    {
        delete grandchildren[i];
    }

    getch();
    endwin();

    return 0;
}

bool is_valid(int r, int c, int max_row, int max_col)
{
    return r >= 0 && r < max_row && c >= 0 && c < max_col;
}

char **generate_grid(int rows, int cols)
{
    char **grid = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[cols];
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = '#';
        }
    }
    return grid;
}
