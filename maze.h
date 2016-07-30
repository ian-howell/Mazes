#ifndef MAZE_H
#define MAZE_H
#include <ncurses.h>

class Maze
{
    private:
        int rows;
        int cols;
        char** grid;

        bool do_animate;

        /**
         * get_dimensions
         *
         * Guarantees that the numbers of rows and columns are each even,
         * forcing a borderless maze. The borders are then trimmed such that a
         * controlled border of exactly 1 character can be implemented
         */
        void get_dimensions();

        /**
         * generate_grid
         *
         * Generates a grid with
         */
        char **generate_grid();

        /**
         * cut_maze
         *
         * Uses Prim's algorithm to create a random path through the maze
         */
        void cut_maze();

        /**
         * animate
         *
         * Color the maze, then print it to the screen
         */
        void animate();

    public:
        Maze();
        Maze(int row, int col);
        ~Maze();

        int get_rows() const { return rows; }
        int get_cols() const { return cols; }
        char** get_grid() const { return grid; }

        void print();
};
#endif
