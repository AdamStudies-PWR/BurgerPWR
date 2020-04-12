#ifndef WORKER_H
#define WORKER_H

#include "gamemaster.h"

class Worker
{
private:
  int id;
  //GameMaster data;
public:
  Worker();
  void main_loop();
private:
};

#endif // WORKER_H
