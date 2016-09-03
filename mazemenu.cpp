#include "mazemenu.h"
#include <cstdlib>
#include <cstring>

void set_flags(char* name, int* f);

const char* yes_or_no[] = {
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

void get_flags()
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
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
    {
        yes_no_items[i] = new_item(yes_or_no[i], NULL);
        set_item_userptr(yes_no_items[i], reinterpret_cast<void*>(set_flags));
    }

    // Title for generation
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Animate generation?");

    // Create generation menu
    generation_menu = new_menu((ITEM**)yes_no_items);
    menu_opts_off(generation_menu, O_SHOWDESC);

    // Set the format
    set_menu_format(generation_menu, 1, size - 1);
    set_menu_fore(generation_menu, COLOR_PAIR(2));
    set_menu_mark(generation_menu, "");

    // Put the generation menu into the global menu box
    set_menu_win(generation_menu, global_menu_win);
    set_menu_sub(generation_menu, derwin(global_menu_win, 1, 0, cur_line++, 26));

    // Post the generation menu
    post_menu(generation_menu);

    // Assign solve items
    size = array_size(solve_options);
    solve_items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
    {
        solve_items[i] = new_item(solve_options[i], NULL);
        set_item_userptr(solve_items[i], reinterpret_cast<void*>(set_flags));
    }

    // Title for Solve option
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Solve Method:");

    // Create Solve menu
    solve_menu = new_menu((ITEM**)solve_items);
    menu_opts_off(solve_menu, O_SHOWDESC);

    // Set the format
    set_menu_format(solve_menu, 1, size - 1);
    set_menu_fore(solve_menu, COLOR_PAIR(1));
    set_menu_mark(solve_menu, "");

    // Put the solve menu into the global menu box
    set_menu_win(solve_menu, global_menu_win);
    set_menu_sub(solve_menu, derwin(global_menu_win, 1, 0, cur_line++, 10));

    // Post the solve menu
    post_menu(solve_menu);

    // Assign print items
    size = array_size(print_options);
    print_items = (ITEM**)calloc(size, sizeof(ITEM*));
    for (int i = 0; i < size; i++)
    {
        print_items[i] = new_item(print_options[i], NULL);
        set_item_userptr(print_items[i], reinterpret_cast<void*>(set_flags));
    }

    // Title for print option
    print_in_middle(global_menu_win, cur_line++, 0, WIDTH, "Print Method:");

    // Create print menu
    print_menu = new_menu((ITEM**)print_items);
    menu_opts_off(print_menu, O_SHOWDESC);

    // Set the format
    set_menu_format(print_menu, 1, size - 1);
    set_menu_fore(print_menu, COLOR_PAIR(1));
    set_menu_mark(print_menu, "");

    // Put the print menu into the global menu box
    set_menu_win(print_menu, global_menu_win);
    set_menu_sub(print_menu, derwin(global_menu_win, 1, 0, cur_line++, 14));

    // Post the print menu
    post_menu(print_menu);
    wrefresh(global_menu_win);      /* Show that box     */

    // Create a list of all menus
    MENU* menus[3] = {
        generation_menu,
        solve_menu,
        print_menu
    };

    int cur_menu = 0;

    int flags = 0;
    int c;
    while (1)
    {
        c = getch();
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
            case 10: /* Enter */
            {
                // I'm so sorry
                ITEM* cur;
                void (*p)(char*, int*);

                cur = current_item(menus[cur_menu]);

                // Horrible cast: item_userptr returns a void*. And that's just
                // sunshine and rainbows. _if you're using C_. But we're not.
                // We're using C++. So the compiler is picky.
                //
                // Enter: reinterpret_cast. We give this guy some bits and it
                // basically just throws them to the wind. It's unfortunately
                // the only way to use userptrs in C++ without actually
                // modifying Ncurses
                p = reinterpret_cast<void (*)(char*, int*)>(item_userptr(cur));
                p((char*)item_name(cur), &flags);
                pos_menu_cursor(menus[cur_menu]);
            }
            break;
        }

        char temp[200];
        ITEM **items;

        items = menu_items(menus[cur_menu]);
        temp[0] = '\0';

        if(flags & 1)
            strcat(temp, "Animate, ");
        else
            strcat(temp, "Don't Animate, ");
        if (flags & 2)
            strcat(temp, "Backtracking, ");
        else
            strcat(temp, "Manual, ");

        move(20, 0);
        clrtoeol();
        mvprintw(20, 0, temp);
        wrefresh(global_menu_win);

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

void set_flags(char* name, int* f)
{
    if (!strcmp(name, "Yes"))
    {
        *f |= 1;
    }
    else if (!strcmp(name, "No"))
    {
        *f &= (1 ^ ~0);
    }

    if (!strcmp(name, "Backtracking"))
    {
        *f |= 2;
    }
    else if (!strcmp(name, "Manual"))
    {
        *f &= (2 ^ ~0);
    }
}
