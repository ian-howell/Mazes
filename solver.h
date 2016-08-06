#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"

class Solver
{
    private:
        int start_row;
        int start_col;
        int max_row;
        int max_col;
        char** grid;
        bool do_animate;

        void init_grid(Maze* maze);
        void find_start();
        void get_new_cell(int& row, int& col, int dir);
        bool solve_r(int row, int col);
        bool is_valid(int row, int col);
        void animate();

    public:
        Solver(bool animate_flag);
        bool solve(Maze* maze);
};

enum
{
    EAST,
    SOUTH,
    WEST,
    NORTH
};
#endif
