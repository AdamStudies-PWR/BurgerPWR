#ifndef GRAPHICFUNC_H
#define GRAPHICFUNC_H

#include "ncurses.h"
#include <iostream>

#define TITLE 1
#define INFO_BAR 2
#define RESTAURANT 3
#define THREADS 4
#define REGISTER 5
#define SIT 6
#define WINDOW 7

using namespace std;

class GraphicFunc
{
public:
  GraphicFunc();
  string objects[2] = {" 🧢 ", " 🤡 "};
protected:
  int rows = 0;
  int columns = 0;
  void check_size();
  void print_title();
  void draw_game();
  void refresh_bar();
};

#endif // GRAPHICFUNC_H
