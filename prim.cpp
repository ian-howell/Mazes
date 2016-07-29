#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>

using std::vector;

const int SIZE = 99;

class Point
{
    public:
        int x;
        int y;
        Point *p;

        Point(int x, int y, Point *p);
        Point* get_opposite();
};

bool is_valid(Point *p);

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

    Point st(0, 0, NULL);
    grid[st.x][st.y] = 'S';

    vector<Point *> frontier;
    vector<Point *> ops;

    // Add the start node's neighbors to the frontier
    for (int i = -1; i <= 1; i += 2)
    {
        Point *n1 = new Point(Point(st.x + i, st.y, &st));
        Point *n2 = new Point(Point(st.x, st.y + i, &st));

        if (is_valid(n1))
        {
            frontier.push_back(n1);
        }
        else
        {
            delete n1;
        }

        if (is_valid(n2))
        {
            frontier.push_back(n2);
        }
        else
        {
            delete n2;
        }
    }

    Point* ch;
    Point* op;

    while (!frontier.empty())
    {
        int rand_point = rand() % frontier.size();

        ch = frontier[rand_point];

        frontier.erase(frontier.begin() + rand_point);

        op = ch->get_opposite();
        bool op_used = false;

        if (is_valid(op) && grid[op->x][op->y] == '#')
        {
            grid[ch->x][ch->y] = '.';
            grid[op->x][op->y] = '.';

            for (int i = -1; i <= 1; i += 2)
            {
                Point *n1 = new Point(op->x + i, op->y, op);
                Point *n2 = new Point(op->x, op->y + i, op);

                if (is_valid(n1) && grid[n1->x][n1->y] == '#')
                {
                    frontier.push_back(n1);
                    op_used = true;
                }
                else
                {
                    delete n1;
                }

                if (is_valid(n2) && grid[n2->x][n2->y] == '#')
                {
                    frontier.push_back(n2);
                    op_used = true;
                }
                else
                {
                    delete n2;
                }
            }
            // Animate here
        }

        delete ch;

        if (!op_used)
        {
            delete op;
        }
        else
        {
            ops.push_back(op);
        }

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

    for (int i = 0; i < (int)ops.size(); i++)
    {
        delete ops[i];
    }

    return 0;
}

bool is_valid(Point* p)
{
    return p->x >= 0 && p->x < SIZE && p->y >= 0 && p->y < SIZE;
}

Point::Point(int x, int y, Point* p)
{
    this->x = x;
    this->y = y;
    this->p = p;
}

Point* Point::get_opposite()
{
    if (p->x - x == 0)
    {
        if (p->y - y == -1)
            return new Point(x, y + 1, NULL);
        else
            return new Point(x, y - 1, NULL);
    }
    else
    {
        if (p->x - x == -1)
            return new Point(x + 1, y, NULL);
        else
            return new Point(x - 1, y, NULL);
    }
}
