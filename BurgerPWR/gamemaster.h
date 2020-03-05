#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <ncurses.h>

using namespace std;

class GameMaster
{
private:
  //zmienne
  bool end = false;
  //metody
  void draw_game();
  void main_loop();
  void check_keyboard();
public:
  bool getEnd();
  void setEnd(bool end);
  GameMaster();
};

#endif // GAMEMASTER_H
