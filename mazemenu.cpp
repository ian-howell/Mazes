#include "mazemenu.h"
#include <cstdlib>
#include <cstring>

const char* yes_or_no[] = {
    "Yes",
    "No",
    (char*)NULL
};

const char* solve_options[] = {
    "Backtracking",
    "Manual",
    (char*)NULL
};

const char* print_options[] = {
    "Solved",
    "Unsolved",
    "None",
    (char*)NULL
};

void get_flags()
{
    int cur_line = 1;             // Keep track of which line we're on

    WINDOW *global_menu_win;

    ITEM** yes_no_items;
    MENU* generation_menu;

    ITEM** solve_items;
    MENU* solve_menu;

    ITEM** print_items;
    MENU* print_menu;

    int size;                        // To keep track of array sizes

    // Create menu box
    global_menu_win = newwin(HEIGHT, WIDTH, 2, (COLS - WIDTH) / 2);
    keypad(global_menu_win, TRUE);

    // Give the menu box a border
    box(global_menu_win, 0 , 0);

    // Add a title to the menu box
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Maze");

    // Seperate the title and the content
    mvwaddch(global_menu_win, cur_line, 0, ACS_LTEE);
    mvwhline(global_menu_win, cur_line, 1, ACS_HLINE, WIDTH - 2);
    mvwaddch(global_menu_win, cur_line, WIDTH - 1, ACS_RTEE);
    cur_line++;

    // Assign yes and no to items
    size = array_size(yes_or_no);
    yes_no_items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
        yes_no_items[i] = new_item(yes_or_no[i], NULL);

    // Title for generation
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Animate generation?");

    // Create generation menu
    generation_menu = new_menu((ITEM**)yes_no_items);

    // Set the format to ONE row and TWO columns
    set_menu_format(generation_menu, 1, 2);

    // Put the generation menu into the global menu box
    set_menu_win(generation_menu, global_menu_win);
    set_menu_sub(generation_menu, derwin(global_menu_win, 1, 0, cur_line++, 15));

    // Post the generation menu
    post_menu(generation_menu);

    // Assign solve items
    size = array_size(solve_options);
    solve_items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
        solve_items[i] = new_item(solve_options[i], NULL);

    // Title for Solve option
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Solve Method:");

    // Create Solve menu
    solve_menu = new_menu((ITEM**)solve_items);

    // Set the format to ONE row and TWO columns
    set_menu_format(solve_menu, 1, 2);

    // Put the solve menu into the global menu box
    set_menu_win(solve_menu, global_menu_win);
    set_menu_sub(solve_menu, derwin(global_menu_win, 1, 0, cur_line++, 8));

    // Post the solve menu
    post_menu(solve_menu);

    // Assign print items
    size = array_size(print_options);
    print_items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
        print_items[i] = new_item(print_options[i], NULL);

    // Title for print option
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Print Method:");

    // Create print menu
    print_menu = new_menu((ITEM**)print_items);

    // Set the format to ONE row and TWO columns
    set_menu_format(print_menu, 1, 2);

    // Put the print menu into the global menu box
    set_menu_win(print_menu, global_menu_win);
    set_menu_sub(print_menu, derwin(global_menu_win, 1, 0, cur_line++, 9));

    // Post the print menu
    post_menu(print_menu);
    wrefresh(global_menu_win);      /* Show that box     */

    int c;
    while ((c = getch()) != 10)
    {
        // Do nothing, for now
    }

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
