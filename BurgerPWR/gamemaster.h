#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <chrono>
#include "graphicfunc.h"

#define INFO_BAR 2
#define RESTAURANT 3
#define WORKER 4
#define CLIENT 5

using namespace std;

class GameMaster: public GraphicFunc
{
private:
  //zmienne
  bool end = false;
  //metody
  void main_loop();
  void check_keyboard();
public:
  bool getEnd();
  void setEnd(bool end);
  GameMaster();
};

#endif // GAMEMASTER_H
