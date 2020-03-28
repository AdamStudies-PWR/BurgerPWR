#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <chrono>
#include "graphicfunc.h"

class GameMaster: public GraphicFunc
{
private:
  //zmienne rozgrywki
  bool mode;
  const int max_clients = 16;
  int clients = 0;
  int prices[5];
  int cost[5];
  int pay;
  int workers;
  //zmienne
  int labor = 0;
  bool end = false;
  int income = 0;
  int loss = 0;
  int budget = 10000;
  int hour[2] = {0, 8};
  int minutes[2] = {0, 0};
  int day[4] = {0, 0, 0, 0};
  int current = 0;
  string selection = "🍔";
  string choice[7] = {selection, "  ", "  ", "  ", "  ", "  ", "  "};
  string emoji[7] = {"🍔", "🍟", "🥤", "🍕", "🥙", "🧢", "💵"};
  //metody
  void main_loop();
  void check_keyboard();
  void timer();
  void calculate_cost();
  void side_UI();
public:
  bool getEnd();
  void setEnd(bool end);
  GameMaster(bool mode, int prices[5], int cost[5], int pay, int workers);
};

#endif // GAMEMASTER_H
