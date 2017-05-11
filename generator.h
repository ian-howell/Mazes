#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <ncurses.h>
#include "maze.h"

class Generator
{
    private:
        Maze* maze;

        /**
         * animate
         *
         * Color the maze, then print it to the screen
         */
        void animate();

    public:
        Generator(Maze* maze);

        /**
         * create_maze
         *
         * Uses Prim's algorithm to create a random path through the maze
         */
        void create_maze(bool animate=false);
};
#endif
