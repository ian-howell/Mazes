#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>

using std::vector;

const int SIZE = 99;

class Cell
{
    public:
        int row;
        int col;
        Cell *parent;

        Cell(int row, int col, Cell *parent);
        Cell* get_opposite();
};

bool is_valid(Cell *parent);

int main()
{
    srand(time(NULL));

    char **grid = (char **)malloc(SIZE * sizeof(char *));
    for (int i = 0; i < SIZE; i++)
    {
        grid[i] = (char *)malloc(SIZE * sizeof(char));
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = '#';
        }
    }

    Cell start(0, 0, NULL);
    grid[start.row][start.col] = 'S';

    vector<Cell *> frontier;

    // Add the start node's neighbors to the frontier
    for (int i = -1; i <= 1; i += 2)
    {
        Cell *n1 = new Cell(Cell(start.row + i, start.col, &start));
        Cell *n2 = new Cell(Cell(start.row, start.col + i, &start));

        if (is_valid(n1))
            frontier.push_back(n1);
        else
            delete n1;

        if (is_valid(n2))
            frontier.push_back(n2);
        else
            delete n2;
    }

    Cell* child;
    Cell* grandchild;
    vector<Cell *> grandchildren;
    bool gc_used = false;

    while (!frontier.empty())
    {
        int rand_point = rand() % frontier.size();
        child = frontier[rand_point];
        frontier.erase(frontier.begin() + rand_point);

        grandchild = child->get_opposite();
        gc_used = false;


        if (is_valid(grandchild) && grid[grandchild->row][grandchild->col] == '#')
        {
            grid[child->row][child->col] = '.';
            grid[grandchild->row][grandchild->col] = '.';

            for (int i = -1; i <= 1; i += 2)
            {
                Cell *n1 = new Cell(grandchild->row + i, grandchild->col, grandchild);
                Cell *n2 = new Cell(grandchild->row, grandchild->col + i, grandchild);

                if (is_valid(n1) && grid[n1->row][n1->col] == '#')
                {
                    frontier.push_back(n1);
                    gc_used = true;
                }
                else
                {
                    delete n1;
                }

                if (is_valid(n2) && grid[n2->row][n2->col] == '#')
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

    for (int i = 0; i < SIZE + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("#");
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("#\n");
    }

    for (int i = 0; i < SIZE + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        free(grid[i]);
    }
    free(grid);

    for (int i = 0; i < (int)grandchildren.size(); i++)
    {
        delete grandchildren[i];
    }

    return 0;
}

bool is_valid(Cell* p)
{
    return p->row >= 0 && p->row < SIZE && p->col >= 0 && p->col < SIZE;
}

Cell::Cell(int row, int col, Cell* parent)
{
    this->row = row;
    this->col = col;
    this->parent = parent;
}

Cell* Cell::get_opposite()
{
    if (parent->row - row == 0)
    {
        if (parent->col - col == -1)
            return new Cell(row, col + 1, NULL);
        else
            return new Cell(row, col - 1, NULL);
    }
    else
    {
        if (parent->row - row == -1)
            return new Cell(row + 1, col, NULL);
        else
            return new Cell(row - 1, col, NULL);
    }
}
