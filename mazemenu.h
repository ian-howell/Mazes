#ifndef MAZEMENU
#define MAZEMENU
#include <menu.h>

#define array_size(a) (sizeof(a) / sizeof(a[0]))

const int WIDTH = 60;
const int HEIGHT = 10;

void get_flags();
void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);

int check_bit(int f, int bitno);
void set_bit(int* f, int bitno);
void unset_bit(int* f, int bitno);

#endif
