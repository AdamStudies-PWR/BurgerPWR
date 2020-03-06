#ifndef GRAPHICFUNC_H
#define GRAPHICFUNC_H

#include "ncurses.h"

#define TITLE 1
#define INFO_BAR 2
#define RESTAURANT 3
#define WORKER 4
#define CLIENT 5
#define REGISTER 6
#define SIT 7

class GraphicFunc
{
public:
  GraphicFunc();
protected:
  int rows = 0;
  int columns = 0;
  void check_size();
  void print_title();
  void draw_game();
};

#endif // GRAPHICFUNC_H
