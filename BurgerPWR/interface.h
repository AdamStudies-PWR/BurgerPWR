#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "ncurses.h"
#include "gamemaster.h"

using namespace std;

class Interface
{
private:
  //Zmienne
  int workers = 3;
  const int clients = 12;
  int existing_clients = 0;
  int rows = 0;
  int columns = 0;
  int pay = 15;
  string selection = "🍔";
  bool highscore = false;
  int prices[5] = {10, 8, 5, 14, 12};
  int production[5] = {3, 2, 2, 5, 4};
  //Metody
  void check_size();
  void print_title();
  bool set_up();
  void set_prices();
public:
  Interface();
  void main_menu();
};

#endif // INTERFACE_H
