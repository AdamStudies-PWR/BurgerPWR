#ifndef GRAPHICFUNC_H
#define GRAPHICFUNC_H

#include "ncurses.h"

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
