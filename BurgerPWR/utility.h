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
#define TEXT 8

using namespace std;

class Utility
{
public:
  Utility();
  void draw_cash(int index);
  void clear_cash(int index);
  void draw_petent(int index);
  void clear_petent(int index);
  void draw_cook(int index);
  void update_cook(int index, float progress);
  void clear_cook(int index);
  void draw_take();
  void clear_take();
  void draw_ctake();
  void clear_ctake();
  void draw_seat(int index, int *food, int size);
  void update_seat(int index, float progress);
  void clear_seat(int index);
  void draw_line(int length);
  void draw_line2(int length);
  void draw_line3(int length);
  void draw_line4(int length);
  void draw_line5(int length);

  bool drawing = false;
  mutex m;
protected:
  string emoji[7] = {"🍔", "🍟", "🥤", "🍕", "🥙", "🧢", "💵"};
  string objects[2] = {" 🧢 ", " 🤡 "};

  int rows = 0;
  int columns = 0;
  void check_size();
  void print_title();
  void draw_game();
  void refresh_bar();
  void endGame();
};

#endif // GRAPHICFUNC_H
