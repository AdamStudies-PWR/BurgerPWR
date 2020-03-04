#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <threads.h>

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
  GameMaster();
};

#endif // GAMEMASTER_H
