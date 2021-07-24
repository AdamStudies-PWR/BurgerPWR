#ifndef INTERFACE_H
#define INTERFACE_H

#include "gamemaster.h"

using namespace std;

class Interface: public Utility
{
private:
  //Zmienne
  int workers = 3;
  int pay = 15;
  string selection = "🍔";
  bool highscore = false;
  int prices[5] = {10, 8, 5, 14, 12};
  int production[5] = {3, 2, 2, 5, 4};
  //Metody
  bool set_up();
  void set_prices();
public:
  Interface();
  void main_menu();
};

#endif // INTERFACE_H
