#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <chrono>
#include "graphicfunc.h"

using namespace std;

class GameMaster: public GraphicFunc
{
private:
  //zmienne
  bool end = false;
  int income = 0;
  int loss = 0;
  int budget = 10000;
  int hour[2] = {0, 8};
  int minutes[2] = {0, 0};
  int day[4] = {0, 0, 0, 0};
  //metody
  void main_loop();
  void check_keyboard();
  void timer();
public:
  bool getEnd();
  void setEnd(bool end);
  GameMaster();
};

#endif // GAMEMASTER_H
