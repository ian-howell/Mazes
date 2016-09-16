#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdio.h>

#include "cell.h"
#include "maze.h"
#include "maze_gen.h"

Maze_gen::Maze_gen(Maze* maze, bool animate_flag)
{
    do_animate = animate_flag;
    this->maze = maze;

    srand(time(NULL));
}

void Maze_gen::create_maze()
{
    char** grid = maze->get_grid();
    int rows = maze->get_rows();
    int cols = maze->get_cols();
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

        gc = child->get_child();
        int r = gc->row;
        int c = gc->col;

        if (maze->is_valid(r, c) && grid[r][c] == '#')
        {
            grid[child->row][child->col] = ' ';
            grid[r][c] = 'E';

            for (int i = -1; i <= 1; i += 2)
            {
                if (maze->is_valid(r + i, c))
                {
                    frontier.push_back(new Cell(r + i, c, gc));
                    gc_used = true;
                }

                if (maze->is_valid(r, c + i))
                {
                    frontier.push_back(new Cell(r, c + i, gc));
                    gc_used = true;
                }
            }

            /* if (do_animate) */
            /*     animate(); */
            if (do_animate)
            {
                maze->draw();
                usleep(100000);
            }

            grid[r][c] = ' ';
        }

        delete child;

        (!gc_used) ?  delete gc : grandchildren.push_back(gc);
    }

    grid[rows - 1][cols - 1] = 'E';
    /* if (do_animate) */
    /*     animate(); */
    if (do_animate)
    {
        maze->draw();
        usleep(100000);
    }

    for (int i = 0; i < (int)grandchildren.size(); i++)
    {
        delete grandchildren[i];
    }
}
