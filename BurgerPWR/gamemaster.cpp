#include "gamemaster.h"

GameMaster::GameMaster()
{
  thread keyboard(&GameMaster::check_keyboard, this);
  keyboard.detach();
  draw_game();
  main_loop();
}

void GameMaster::main_loop()
{
  while(!end)
  {

  }
}

void GameMaster::draw_game()
{

}

void GameMaster::check_keyboard()
{
  while(!this->getEnd())
  {
    int input = getch();
    if(input == 274) this->setEnd(true);
  }
}

//Utility func
bool GameMaster::getEnd() {return end;}
void GameMaster::setEnd(bool end) {this->end = end;}
