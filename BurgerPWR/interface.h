#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

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
  //Metody
  void check_size();
public:
  Interface();
  void main_menu();
};

#endif // INTERFACE_H
