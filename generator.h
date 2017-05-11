#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <ncurses.h>
#include "maze.h"

class Maze_gen
{
    private:
        Maze* maze;
        bool do_animate;

        /**
         * animate
         *
         * Color the maze, then print it to the screen
         */
        void animate();

    public:
        Maze_gen(Maze* maze, bool animate_flag);

        /**
         * create_maze
         *
         * Uses Prim's algorithm to create a random path through the maze
         */
        void create_maze();
};
#endif
