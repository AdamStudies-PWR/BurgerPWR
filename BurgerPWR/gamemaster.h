#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <chrono>
#include "utility.h"
#include <vector>
#include <mutex>

class GameMaster: public Utility
{
private:
  //zmienne rozgrywki
  mutex mx;
  bool mode;
  const int max_clients = 16;
  int clients = 0;
  int prices[5];
  int cost[5];
  int pay;
  int max_workers;
  //zmienne
  vector<thread> workers;

  bool end = false;
  int labor = 0;
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
  string res_emoji[8] = {"🍞", "🥩", "🥗", "🍅", "🥔", "♨️", "🧀", "🥓"};

  int available[8] = {4, 4, 4, 4, 4, 4, 4, 4};

  //metody
  void main_loop();
  void check_keyboard();
  void timer();
  void calculate_cost();
  void side_UI();
  void resources_info();
public:
  bool getEnd();
  void setEnd(bool end);
  GameMaster(bool mode, int prices[5], int cost[5], int pay, int workers);
  GameMaster();
};

class Worker
{
private:
    GameMaster *master;
    int index;
    int state = 0;
public:
    Worker(int index, GameMaster *master);
    ~Worker();

    void main_loop();
private:
};

#endif // GAMEMASTER_H
