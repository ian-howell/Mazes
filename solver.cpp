#include <unistd.h>
#include "solver.h"
#include "cell.h"
#include <cstdio>
#include <ncurses.h>

Solver::Solver(Maze* maze, bool animate_flag)
{
    do_animate = animate_flag;
    this->maze = maze;
    grid = maze->get_grid();
    find_start();
}

void Solver::find_start()
{
    int max_row = maze->get_rows();
    int max_col = maze->get_cols();

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

bool Solver::backtrack()
{
    return backtrack_r(start_row, start_col);
}

bool Solver::backtrack_r(int row, int col)
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
            {
                maze->draw();
                usleep(100000);
            }

            if (backtrack_r(r, c))
            {
                return true;
            }
            else
            {
                grid[r][c] = ' ';
                dir++;

                if (do_animate)
                {
                    maze->draw();
                    usleep(100000);
                }
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
    bool retval = true;

    if (maze->is_valid(row, col))
    {
        switch (grid[row][col])
        {
            case '.':
            case '#':
            case 'S':
                retval = false;
        }
    }
    else
    {
        retval = false;
    }

    return retval;
}
