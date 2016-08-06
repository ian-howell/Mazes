#include <unistd.h>
#include "solver.h"
#include "cell.h"

Solver::Solver(bool animate_flag)
{
    do_animate = animate_flag;
}

void Solver::init_grid(Maze* maze)
{
    grid = maze->get_grid();
    max_row = maze->get_rows();
    max_col = maze->get_cols();

    find_start();
}

void Solver::find_start()
{
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            if (grid[i][j] == 'S')
            {
                start_row = i;
                start_col = j;
                return;
            }
        }
    }
}

bool Solver::solve(Maze* maze)
{
    init_grid(maze);

    return solve_r(start_row, start_col);
}

bool Solver::solve_r(int row, int col)
{
    int dir = 0;
    do
    {
        int r = row;
        int c = col;

        get_new_cell(r, c, dir);

        if (is_valid(r, c))
        {
            if (grid[r][c] == 'E')
                return true;

            grid[r][c] = '.';

            if (do_animate)
                animate();

            if (solve_r(r, c))
            {
                return true;
            }
            else
            {
                grid[r][c] = ' ';
                dir++;

                if (do_animate)
                    animate();
            }
        }
        else
        {
            dir++;
        }
    } while (dir < 4);
    return false;
}

void Solver::get_new_cell(int& row, int& col, int dir)
{
    switch(dir)
    {
        case NORTH:
            row--;
            break;
        case EAST:
            col++;
            break;
        case SOUTH:
            row++;
            break;
        case WEST:
            col--;
            break;
    }
}

bool Solver::is_valid(int row, int col)
{
    if (row < 0 || col < 0 || row >= max_row || col >= max_col)
        return false;

    switch (grid[row][col])
    {
        case '.':
        case '#':
        case 'S':
            return false;
    }

    return true;
}

void Solver::animate()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            if (grid[i][j] == '#')
                attron(COLOR_PAIR(1));
            else if (grid[i][j] == ' ')
                attron(COLOR_PAIR(2));
            else if (grid[i][j] == 'S')
                attron(COLOR_PAIR(3));
            else if (grid[i][j] == '.')
                attron(COLOR_PAIR(5));
            else
                attron(COLOR_PAIR(4));

            mvwprintw(stdscr, i + 1, j + 1, " ");

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));
        }
    }
    refresh();
    usleep(100000);
}
