#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <chrono>
#include "utility.h"
#include <vector>

struct kasa
{
    bool busy = false;
    bool take = true;
    mutex m;
    int *order;
    bool isready = false;
    bool payed = true;
    int index;

    kasa(int index)
    {
        this->index = index;
    }
};

class GameMaster: public Utility
{
private:
  //zmienne rozgrywki
  bool mode;
  const int max_clients = 16;
  int clients = 0;
  int history = 0;
  int prices[5];
  int cost[5];
  int pay;
  int max_workers;
  //zmienne
  vector<thread> workers;

  bool end = false;
  int labor = 0;
  int loss = 0;
  int income = 0;
  int budget = 10000;
  int hour[2] = {0, 8};
  int minutes[2] = {0, 0};
  int day[4] = {0, 0, 0, 0};
  int current = 0;

  string selection = "🍔";
  string choice[7] = {selection, "  ", "  ", "  ", "  ", "  ", "  "};
  string emoji[7] = {"🍔", "🍟", "🥤", "🍕", "🥙", "🧢", "💵"};

  kasa *k1;
  kasa *k2;
  kasa *k3;

  //metody
  void main_loop();
  void check_keyboard();
  void timer();
  void calculate_cost();
  void side_UI();
  void resources_info();
  void start_client();
public:
  mutex m;
  int line = 0;
  int line2 = 0;
  int line3 = 0;
  bool getEnd();
  void setEnd(bool end);
  GameMaster(bool mode, int prices[5], int cost[5], int pay, int workers);
  GameMaster();
  ~GameMaster();
};

class Worker
{
private:
    GameMaster *master;
    kasa *k1;
    kasa *k2;
    kasa *k3;

    kasa *chosen;

    int *order;
    int index;
    int state = 0;
    int time;
public:
    Worker(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3);
    ~Worker();

    void main_loop();
private:
    void begin();
    void wait();
    void take_order();
};

class Client
{
private:
    GameMaster *master;
    kasa *k1;
    kasa *k2;
    kasa *k3;

    kasa *chosen;

    int index;
    int state = 0;
    int *order;
public:
    Client(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3);
    ~Client();

    void main_loop();
private:
    void begin();
    void wait();
    void give_order();
    void wait2();
};

#endif // GAMEMASTER_H
