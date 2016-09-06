#ifndef MAZEMENU
#define MAZEMENU
#include <menu.h>

#define array_size(a) (sizeof(a) / sizeof(a[0]))

const int WIDTH = 60;
const int HEIGHT = 10;

int get_flags();
void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);

int check_bit(int f, int bitno);
void set_bit(int* f, int bitno);
void unset_bit(int* f, int bitno);

ITEM** get_items(const char* options[], int size);

void set_format(MENU* menu, int size);

void print_flag_status(int flags, int lineno);

#endif
