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

struct kitchen
{
    bool busy = false;
    int index;
    mutex m;

    kitchen(int index)
    {
        this->index = index;
    }

    kitchen() {}
};

struct takeaway
{
    bool busy = false;
    int mealfor = -1;
    mutex m;
};

class GameMaster: public Utility
{
private:
  //zmienne rozgrywki
  bool mode;
  const int max_clients = 16;
  int clients = 0;
  int history = 0;
  int cost[5];
  int pay;
  int max_workers;
  //zmienne
  vector<thread> workers;

  bool end = false;
  int labor = 0;
  int loss = 0;
  int budget = 10000;
  int hour[2] = {0, 8};
  int minutes[2] = {0, 0};
  int day[4] = {0, 0, 0, 0};
  int current = 0;

  string selection = "🍔";
  string choice[7] = {selection, "  ", "  ", "  ", "  ", "  ", "  "};

  kasa *k1;
  kasa *k2;
  kasa *k3;
  kitchen *c1;
  kitchen *c2;
  kitchen *c3;
  kitchen *c4;
  kitchen *c5;
  kitchen *c6;
  kitchen *c7;
  kitchen *c8;
  takeaway *tk;

  bool seats[8] = {false, false, false, false, false, false, false, false};

  //metody
  void main_loop();
  void check_keyboard();
  void timer();
  void calculate_cost();
  void side_UI();
  void resources_info();
  void start_client();
  void sleep();
public:
  int line = 0;
  int line2 = 0;
  int line3 = 0;
  int line4 = 0;
  int line5 = 0;
  int income = 0;
  int prices[5];

  bool getEnd();
  void setEnd(bool end);
  void decreaseClients();
  GameMaster(bool mode, int prices[5], int cost[5], int pay, int workers);
  GameMaster();
  ~GameMaster();
};

class Client
{
private:
    GameMaster *master;
    kasa *k1;
    kasa *k2;
    kasa *k3;

    takeaway *tk;
    kasa *chosen;
    bool *seats;

    int index;
    int state = 0;
    int *order;
    int time;
    int counter = 0;
    int seat_id;
    int osize;
public:
    Client(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3, takeaway *tk, bool *seats);
    ~Client();

    void main_loop();
private:
    void begin();
    void wait();
    void give_order();
    void wait2();
    void take_food();
    void eat();
    void wait3();
    void sleep();
};

class Worker
{
private:
    GameMaster *master;
    kasa *k1;
    kasa *k2;
    kasa *k3;
    kitchen *c1;
    kitchen *c2;
    kitchen *c3;
    kitchen *c4;
    kitchen *c5;
    kitchen *c6;
    kitchen *c7;
    kitchen *c8;

    takeaway *tk;
    kasa *chosen;
    kitchen *cooker;

    int *order;
    int index;
    int state = 0;
    int time;
    int order_for = -1;
    int counter = 0;
public:
    Worker(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3, kitchen *c1, kitchen *c2, kitchen *c3, kitchen *c4, kitchen *c5, kitchen *c6, kitchen *c7, kitchen *c8, takeaway *tk);
    ~Worker();

    void main_loop();
private:
    void begin();
    void wait();
    void take_order();
    void choose_cooker();
    void give_food();
    void cook();
    void wait2();
    void end();
    void sleep();
};

#endif // GAMEMASTER_H
