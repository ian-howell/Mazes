#include <ncurses.h>
#include "player.h"
#include "maze.h"

Player::Player(Maze* maze, int row, int col)
{
    this->game_won = false;
    this->row = row;
    this->col = col;

    this->maze = maze;

}

void Player::move(direction dir)
{
    int newcol = col;
    int newrow = row;

    char** grid = maze->get_grid();

    switch (dir)
    {
        case LEFT:
            if (is_valid(row, col - 1))
                newcol--;
            break;
        case RIGHT:
            if (is_valid(row, col + 1))
                newcol++;
            break;
        case UP:
            if (is_valid(row - 1, col))
                newrow--;
            break;
        case DOWN:
            if (is_valid(row + 1, col))
                newrow++;
            break;
    }

    if (grid[newrow][newcol] == 'E')
    {
        game_won = true;
        grid[row][col] = '.';
        return;
    }
    else if (grid[newrow][newcol] == '.')
        grid[row][col] = ' ';
    else
        grid[row][col] = '.';

    // Print the player in the new location
    row = newrow;
    col = newcol;
    grid[row][col] = 'S';
}

bool Player::is_valid(int row, int col)
{
    bool retval = true;

    if (maze->is_valid(row, col))
    {
        if (maze->get_grid()[row][col] == '#')
            retval = false;
    }
    else
    {
        retval = false;
    }

    return retval;
}
