#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <ncurses.h>
#include "cell.h"

bool is_valid(Cell *parent, int r, int c);

int main()
{
    initscr();
    int cols, rows;
    getmaxyx(stdscr, rows, cols);
    endwin();

    if (cols % 2 == 0)
        cols -= 3;
    else
        cols -= 2;

    if (rows % 2 == 0)
        rows -= 3;
    else
        rows -= 2;

    srand(time(NULL));

    /* char **grid = (char **)malloc(rows * sizeof(char *)); */
    char **grid = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        /* grid[i] = (char *)malloc(cols * sizeof(char)); */
        grid[i] = new char[cols];
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = '#';
        }
    }

    Cell start(0, 0, NULL);
    grid[start.row][start.col] = 'S';

    std::vector<Cell *> frontier;

    // Add the start node's neighbors to the frontier
    for (int i = -1; i <= 1; i += 2)
    {
        Cell *n1 = new Cell(Cell(start.row + i, start.col, &start));
        Cell *n2 = new Cell(Cell(start.row, start.col + i, &start));

        if (is_valid(n1, rows, cols))
            frontier.push_back(n1);
        else
            delete n1;

        if (is_valid(n2, rows, cols))
            frontier.push_back(n2);
        else
            delete n2;
    }

    Cell* child;
    Cell* grandchild;
    std::vector<Cell *> grandchildren;
    bool gc_used = false;

    while (!frontier.empty())
    {
        int rand_point = rand() % frontier.size();
        child = frontier[rand_point];
        frontier.erase(frontier.begin() + rand_point);

        grandchild = child->get_opposite();
        gc_used = false;


        if (is_valid(grandchild, rows, cols) && grid[grandchild->row][grandchild->col] == '#')
        {
            grid[child->row][child->col] = '.';
            grid[grandchild->row][grandchild->col] = '.';

            for (int i = -1; i <= 1; i += 2)
            {
                Cell *n1 = new Cell(grandchild->row + i, grandchild->col, grandchild);
                Cell *n2 = new Cell(grandchild->row, grandchild->col + i, grandchild);

                if (is_valid(n1, rows, cols) && grid[n1->row][n1->col] == '#')
                {
                    frontier.push_back(n1);
                    gc_used = true;
                }
                else
                {
                    delete n1;
                }

                if (is_valid(n2, rows, cols) && grid[n2->row][n2->col] == '#')
                {
                    frontier.push_back(n2);
                    gc_used = true;
                }
                else
                {
                    delete n2;
                }
            }
            // Animate here
        }

        delete child;

        if (!gc_used)
            delete grandchild;
        else
            grandchildren.push_back(grandchild);

    }

    for (int i = 0; i < cols + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf("#");
        for (int j = 0; j < cols; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("#\n");
    }

    for (int i = 0; i < cols + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        delete [] grid[i];
    }
    delete [] grid;

    for (int i = 0; i < (int)grandchildren.size(); i++)
    {
        delete grandchildren[i];
    }

    return 0;
}

bool is_valid(Cell* p, int r, int c)
{
    return p->row >= 0 && p->row < r && p->col >= 0 && p->col < c;
}
