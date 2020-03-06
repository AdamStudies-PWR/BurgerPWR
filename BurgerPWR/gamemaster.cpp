#include "gamemaster.h"

GameMaster::GameMaster()
{
  draw_game();
  nodelay(stdscr, true);
  thread keyboard(&GameMaster::check_keyboard, this);
  keyboard.detach();
  main_loop();
}

void GameMaster::timer()
{
  if((minutes[0] + 1) > 5)
  {
    minutes[0] = 0;
    if((hour[1] + 1) > 9)
    {
      hour[1] = 0;
      if((hour[0] + 1) > 1)
      {
        hour[0] = 0;
        hour[1] = 8;
        if((day[3] + 1) > 9)
        {
           day[3] = 0;
           if((day[2] + 1) > 9)
           {
              day[2] = 0;
              if((day[1] + 1) > 9)
              {
                 day[1] = 0;
                 day[0]++;
              }
              else day[1]++;
           }
           else day[2]++;
        }
        else day[3]++;
      }
      else hour[0]++;
    }
    else hour[1]++;
  }
  else minutes[0]++;
}

void GameMaster::main_loop()
{
  while(!end)
  {
    attron(COLOR_PAIR(INFO_BAR));
    mvprintw(0, 0, "Dzień: %d%d%d%d   Czas: %d%d:%d%d", day[0], day[1], day[2], day[3], hour[0], hour[1], minutes[0], minutes[1]);
    mvprintw(rows - 1, 0, "Przychód: %d$ \t\t Straty: %d$", income, loss);
    mvprintw(rows - 1, columns - 20, "Budżet: %d$", budget);
    timer();
    attroff(COLOR_PAIR(INFO_BAR));
    this_thread::sleep_for(chrono::milliseconds(800));
  }
}

void GameMaster::check_keyboard()
{
  while(!this->getEnd())
  {
    int input = getch();
    if(input == 274) this->setEnd(true);
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}

//Utility func
bool GameMaster::getEnd() {return end;}
void GameMaster::setEnd(bool end) {this->end = end;}
