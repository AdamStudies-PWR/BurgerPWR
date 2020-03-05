#include "gamemaster.h"

GameMaster::GameMaster()
{
  init_pair(2, COLOR_WHITE, COLOR_RED);
  thread keyboard(&GameMaster::check_keyboard, this);
  keyboard.detach();
  draw_game();
  main_loop();
}

void GameMaster::main_loop()
{
  while(!end)
  {
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void GameMaster::check_keyboard()
{
  while(!this->getEnd())
  {
    int input = getch();
    if(input == 274) this->setEnd(true);
    this_thread::sleep_for(chrono::seconds(1));
  }
}

//Utility func
bool GameMaster::getEnd() {return end;}
void GameMaster::setEnd(bool end) {this->end = end;}
