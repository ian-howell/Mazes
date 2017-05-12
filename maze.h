#ifndef MAZE_H
#define MAZE_H

#define DRAW_DELAY 50000

class Maze
{
 private:
  int rows;
  int cols;
  char** grid;

 public:
  Maze(int row, int col);
  Maze(const char* filename);
  ~Maze();

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }
  char** get_grid() const { return grid; }

  void init_curses();

  void print(const char* filename);

  void draw();

  bool is_valid(int r, int c);
};
#endif
