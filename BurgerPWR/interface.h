#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "pthread.h"
#include "ncurses.h"

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
  char selection[10] = "🍔";
  bool highscore = false;
  //Metody
  void check_size();
  void print_title();
  void set_up();
public:
  Interface();
  void main_menu();
};

#endif // INTERFACE_H
