#ifndef MAZEMENU
#define MAZEMENU
#include <menu.h>

const int GEN_NUM = 2;
const int WIDTH = 40;
const int HEIGHT = 10;

void get_flags();
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

#endif
