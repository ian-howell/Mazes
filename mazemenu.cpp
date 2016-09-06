#include "mazemenu.h"
#include <cstdlib>
#include <cstring>

void set_flags(char* name, int* f);

const char* gen_options[] = {
    "Yes",
    "No",
    (char*)NULL
};

const char* solve_options[] = {
    "No Solve",
    "Manual",
    "Backtracking",
    (char*)NULL
};

const char* print_options[] = {
    "No Print",
    "Solved",
    "Unsolved",
    "Both",
    (char*)NULL
};

int get_flags()
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    int cur_line = 1;             // Keep track of which line we're on
    int cur_menu = 0;             // Keep track of which menu we're manipulating
    int flags = 0;                // The return value

    WINDOW *global_menu_win;

    ITEM** gen_items;
    MENU* gen_menu;

    ITEM** solve_items;
    MENU* solve_menu;

    ITEM** print_items;
    MENU* print_menu;

    // Create menu box
    global_menu_win = newwin(HEIGHT, WIDTH, 2, (COLS - WIDTH) / 2);
    keypad(global_menu_win, TRUE);
    box(global_menu_win, 0 , 0);
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Maze");
    mvwaddch(global_menu_win, cur_line, 0, ACS_LTEE);
    mvwhline(global_menu_win, cur_line, 1, ACS_HLINE, WIDTH - 2);
    mvwaddch(global_menu_win, cur_line, WIDTH - 1, ACS_RTEE);
    cur_line++;

    // Create generation menu
    gen_items = get_items(gen_options, array_size(gen_options));
    gen_menu = new_menu((ITEM**)gen_items);
    set_format(gen_menu, array_size(gen_options));
    set_menu_fore(gen_menu, COLOR_PAIR(2));
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Animate generation?");

    // Post the generation menu
    set_menu_win(gen_menu, global_menu_win);
    set_menu_sub(gen_menu, derwin(global_menu_win, 1, 0, cur_line++, 26));
    post_menu(gen_menu);

    // Create Solve menu
    solve_items = get_items(solve_options, array_size(solve_options));
    solve_menu = new_menu((ITEM**)solve_items);
    set_format(solve_menu, array_size(solve_options));
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Solve Method");

    // Post the solve menu
    set_menu_win(solve_menu, global_menu_win);
    set_menu_sub(solve_menu, derwin(global_menu_win, 1, 0, cur_line++, 10));
    post_menu(solve_menu);

    // Create print menu
    print_items = get_items(print_options, array_size(print_options));
    print_menu = new_menu((ITEM**)print_items);
    set_format(print_menu, array_size(print_options));
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Print Method");

    // Post the print menu
    set_menu_win(print_menu, global_menu_win);
    set_menu_sub(print_menu, derwin(global_menu_win, 1, 0, cur_line++, 14));
    post_menu(print_menu);

    // Show the menu box
    wrefresh(global_menu_win);

    // Print the status of the flags
    print_flag_status(flags, cur_line);

    // Create a list of all menus
    MENU* menus[3] = { gen_menu, solve_menu, print_menu };

    int c;
    while ((c = getch()) != 10)    // Enter
    {
        switch(c)
        {
            case KEY_RIGHT:
                menu_driver(menus[cur_menu], REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(menus[cur_menu], REQ_LEFT_ITEM);
                break;
            case KEY_UP:
                set_menu_fore(menus[cur_menu], COLOR_PAIR(1));
                if (cur_menu > 0)
                    cur_menu--;
                set_menu_fore(menus[cur_menu], COLOR_PAIR(2));
                break;
            case KEY_DOWN:
                set_menu_fore(menus[cur_menu], COLOR_PAIR(1));
                if (cur_menu < 2)
                    cur_menu++;
                set_menu_fore(menus[cur_menu], COLOR_PAIR(2));
                break;
            case ' ':      // Space
                // Gets the name of the current item from the current menu
                set_flags((char*)item_name(current_item(menus[cur_menu])), &flags);
                break;
        }

        print_flag_status(flags, cur_line);
        wrefresh(global_menu_win);
    }

    return flags;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string)
{
    int length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

void set_flags(char* name, int* f)
{
    if (!strcmp(name, "Yes"))
    {
        set_bit(f, 0);
    }
    else if (!strcmp(name, "No"))
    {
        unset_bit(f, 0);
    }
    else if (!strcmp(name, "No Solve"))
    {
        unset_bit(f, 2);
        unset_bit(f, 1);
    }
    else if (!strcmp(name, "Manual"))
    {
        unset_bit(f, 2);
        set_bit(f, 1);
    }
    else if (!strcmp(name, "Backtracking"))
    {
        set_bit(f, 2);
        unset_bit(f, 1);
    }
    else if (!strcmp(name, "No Print"))
    {
        unset_bit(f, 4);
        unset_bit(f, 3);
    }
    else if (!strcmp(name, "Solved"))
    {
        unset_bit(f, 4);
        set_bit(f, 3);
    }
    else if (!strcmp(name, "Unsolved"))
    {
        set_bit(f, 4);
        unset_bit(f, 3);
    }
    else if (!strcmp(name, "Both"))
    {
        set_bit(f, 4);
        set_bit(f, 3);
    }
}

int check_bit(int f, int bitno)
{
    return f & 1<<bitno;
}

void set_bit(int* f, int bitno)
{
    *f = *f | 1<<bitno;
}

void unset_bit(int* f, int bitno)
{
    *f = *f & ~(1<<bitno);
}

ITEM** get_items(const char* options[], int size)
{
    ITEM** items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
        items[i] = new_item(options[i], NULL);

    return items;
}

void set_format(MENU* menu, int size)
{
    set_menu_format(menu, 1, size - 1);
    set_menu_fore(menu, COLOR_PAIR(1));
    set_menu_mark(menu, "");
}

void print_flag_status(int flags, int lineno)
{
        char gen_temp[40];
        char solve_temp[40];
        char print_temp[40];
        gen_temp[0] = '\0';
        solve_temp[0] = '\0';
        print_temp[0] = '\0';

        if(check_bit(flags, 0)) // XXXX XXX0
            strcat(gen_temp, "Animate");
        else // XXXX XXX1
            strcat(gen_temp, "Don't Animate");

        if (!check_bit(flags, 2) && !check_bit(flags, 1)) // XXXX X00X
            strcat(solve_temp, "Don't solve");
        else if (!check_bit(flags, 2) && check_bit(flags, 1)) // XXXX X01X
            strcat(solve_temp, "Solve with the arrow keys");
        else // XXXX X1XX
            strcat(solve_temp, "Automatically solve with recursive backtracking");

        if (!check_bit(flags, 4) && !check_bit(flags, 3)) // XXX0 0XXX
            strcat(print_temp, "Don't print the maze");
        else if (!check_bit(flags, 4) && check_bit(flags, 3)) // XXX0 1XXX
            strcat(print_temp, "Print the unsolved maze");
        else if (check_bit(flags, 4) && !check_bit(flags, 3)) // XXX1 0XXX
            strcat(print_temp, "Print the solved maze");
        else if (check_bit(flags, 4) && check_bit(flags, 3)) // XXX1 1XXX
            strcat(print_temp, "Print both solved and unsolved mazes");

        int status_line = lineno + 3;

        move(status_line, 0);
        clrtoeol();
        print_in_middle(stdscr, status_line, 0, COLS, gen_temp);

        move(status_line + 1, 0);
        clrtoeol();
        print_in_middle(stdscr, status_line + 1, 0, COLS, solve_temp);

        move(status_line + 2, 0);
        clrtoeol();
        print_in_middle(stdscr, status_line + 2, 0, COLS, print_temp);
}
