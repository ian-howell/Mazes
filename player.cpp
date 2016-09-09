#include <ncurses.h>
#include "player.h"
#include "maze.h"

Player::Player(Maze* maze, int row, int col)
{
    this->row = row;
    this->col = col;

    this->game_won = false;

    init_grid(maze);
}

void Player::init_grid(Maze* maze)
{
    grid = maze->get_grid();
    max_row = maze->get_rows();
    max_col = maze->get_cols();
}

void Player::move(direction dir)
{
    int newcol = col;
    int newrow = row;
    // Erase the player
    /* grid[row][col] = ' '; */
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

void Player::draw()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            if (grid[i][j] == '#')
                attron(COLOR_PAIR(1));
            else if (grid[i][j] == ' ')
                attron(COLOR_PAIR(2));
            else if (grid[i][j] == '.')
                attron(COLOR_PAIR(5));
            else if (grid[i][j] == 'S')
                attron(COLOR_PAIR(3));
            else
                attron(COLOR_PAIR(4));

            mvwprintw(stdscr, i + 1, j + 1, " ");

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));
            attroff(COLOR_PAIR(5));
        }
    }
    refresh();
}

bool Player::is_valid(int row, int col)
{
    if (row < 0 || col < 0 || row >= max_row || col >= max_col)
        return false;

    if (grid[row][col] == '#')
        return false;

    return true;
}
