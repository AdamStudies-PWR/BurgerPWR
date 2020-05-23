#ifndef GRAPHICFUNC_H
#define GRAPHICFUNC_H

#include "ncurses.h"
#include <iostream>
#include <mutex>

#define TITLE 1
#define INFO_BAR 2
#define RESTAURANT 3
#define THREADS 4
#define REGISTER 5
#define SIT 6
#define WINDOW 7

using namespace std;

class Utility
{
public:
  Utility();
  string objects[2] = {" 🧢 ", " 🤡 "};
  void draw_cash(int index);
  void clear_cash(int index);
  void draw_petent(int index);
  void clear_petent(int index);
  void draw_line(int length);
  void draw_line2(int length);
  void draw_line3(int length);
  mutex m;
protected:
  int rows = 0;
  int columns = 0;
  void check_size();
  void print_title();
  void draw_game();
  void refresh_bar();
};

#endif // GRAPHICFUNC_H
