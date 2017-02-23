#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"

class Solver
{
    private:
        int start_row;
        int start_col;
        char** grid;
        bool do_animate;

        Maze* maze;

        void find_start();
        void get_new_cell(int& row, int& col, int dir);
        bool backtrack_r(int row, int col);
        bool is_valid(int row, int col);

    public:
        Solver(Maze* maze, bool animate_flag);
        bool backtrack();
};

enum
{
    EAST,
    SOUTH,
    WEST,
    NORTH
};
#endif
