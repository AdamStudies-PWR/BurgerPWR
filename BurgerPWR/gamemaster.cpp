#include "gamemaster.h"

GameMaster::GameMaster() {}

GameMaster::GameMaster(bool mode, int prices[], int cost[], int pay, int max_workers)
{
  this->mode = mode;
  for(int i=0; i<5; i++)
  {
    this->prices[i] = prices[i];
    this->cost[i] = cost[i];
  }
  this->pay = pay;
  this->max_workers = max_workers;
  draw_game();
  nodelay(stdscr, true);
  for(int i=0; i<max_workers; i++)
  {
      Worker *w = new Worker(i, this);
      workers.emplace_back(&Worker::main_loop, w);
  }
  //for(int i=0; i<max_workers; i++) workers[i].detach();
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

void GameMaster::calculate_cost()
{
  if(labor != hour[1])
  {
    labor = hour[1];
    loss = max_workers * pay;
  }
  else loss = 0;
  budget = budget - loss;
}

void GameMaster::main_loop()
{
  side_UI();
  resources_info();
  while(!end)
  {
    refresh_bar();
    attron(COLOR_PAIR(INFO_BAR));
    mvprintw(0, 0, "Dzień: %d%d%d%d   Czas: %d%d:%d%d", day[0], day[1], day[2], day[3], hour[0], hour[1], minutes[0], minutes[1]);
    mvprintw(rows - 1, 0, "Przychód: %d$ \t\t Straty: %d$", income, loss);
    mvprintw(rows - 1, columns - 20, "Budżet: %d$", budget);
    calculate_cost();
    timer();
    attroff(COLOR_PAIR(INFO_BAR));
    this_thread::sleep_for(chrono::milliseconds(800));
  }
}

void GameMaster::side_UI()
{
  attron(COLOR_PAIR(WINDOW));
  //Jedzenie
  mvprintw(6,0.85*columns,"%s Burger:\t[%s]\t%d$ ", emoji[0].c_str(), choice[0].c_str(),prices[0]);
  mvprintw(7,0.85*columns,"%s Frytki:\t[%s]\t%d$ ", emoji[1].c_str(), choice[1].c_str(),prices[1]);
  mvprintw(8,0.85*columns,"%s Cola:\t[%s]\t%d$ ", emoji[2].c_str(), choice[2].c_str(),prices[2]);
  mvprintw(9,0.85*columns,"%s Pizza:\t[%s]\t%d$ ", emoji[3].c_str(), choice[3].c_str(),prices[3]);
  mvprintw(10,0.85*columns,"%s Kebab:\t[%s]\t%d$ ", emoji[4].c_str(), choice[4].c_str(),prices[4]);
  //Parcownicy
  mvprintw(15,0.85*columns,"%s Ilość:\t[%s]\t%d ", emoji[5].c_str(), choice[5].c_str(), max_workers);
  mvprintw(16,0.85*columns,"%s Pensja:\t[%s]\t%d$/h ", emoji[6].c_str(), choice[6].c_str(),pay);
  attroff(COLOR_PAIR(WINDOW));
}

void GameMaster::resources_info()
{
    attron(COLOR_PAIR(WINDOW));
    mvprintw(21 ,0.86*columns,"%s Bułka:\t\t%d", res_emoji[0].c_str(), available[0]);
    mvprintw(22 ,0.86*columns,"%s Mięso:\t\t%d", res_emoji[1].c_str(), available[1]);
    mvprintw(23 ,0.86*columns,"%s Sałata:\t\t%d", res_emoji[2].c_str(), available[2]);
    mvprintw(24 ,0.86*columns,"%s Pomidor:\t\t%d", res_emoji[3].c_str(), available[3]);
    mvprintw(25 ,0.86*columns,"%s Ziemniaki:\t%d", res_emoji[4].c_str(), available[4]);
    mvprintw(26 ,0.86*columns,"%s  Ciasto:\t\t%d", res_emoji[5].c_str(), available[5]);
    mvprintw(27 ,0.86*columns,"%s Ser:\t\t%d", res_emoji[6].c_str(), available[6]);
    mvprintw(28 ,0.86*columns,"%s Szynka:\t\t%d", res_emoji[7].c_str(), available[7]);
    attroff(COLOR_PAIR(WINDOW));
}

void GameMaster::check_keyboard()
{
  while(!this->getEnd())
  {
    int input = getch();
    switch(input)
    {
      case 274: this->setEnd(true); break;
      case KEY_UP:
      {
        choice[current] = "  ";
        if(current == 0) current = 6;
        else current--;
        choice[current] = selection;
        side_UI();
      } break;
      case KEY_DOWN:
      {
          choice[current] = "  ";
          if(current == 6) current = 0;
          else current++;
          choice[current] = selection;
          side_UI();
      } break;
      case KEY_LEFT:
      {
        switch(current)
        {
          case 0: if(prices[0] - 1 > 3) prices[0]--; break;
          case 1: if(prices[1] - 1 > 2) prices[1]--; break;
          case 2: if(prices[2] - 1 > 2) prices[2]--; break;
          case 3: if(prices[3] - 1 > 5) prices[3]--; break;
          case 4: if(prices[4] - 1 > 4) prices[4]--; break;
          case 6: if(pay - 1 > 7) pay--; break;
        }
        side_UI();
      } break;
      case KEY_RIGHT:
      {
          switch(current)
          {
            case 0: if(prices[0] + 1 < 17) prices[0]++; break;
            case 1: if(prices[1] + 1 < 13) prices[1]++; break;
            case 2: if(prices[2] + 1 < 13) prices[2]++; break;
            case 3: if(prices[3] + 1 < 25) prices[3]++; break;
            case 4: if(prices[4] + 1 < 21) prices[4]++; break;
            case 6: if(pay + 1 < 25) pay++; break;
          }
          side_UI();
      } break;
    }
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}

//Utility func
bool GameMaster::getEnd() {return end;}
void GameMaster::setEnd(bool end) {this->end = end;}

Worker::~Worker()
{
    delete master;
}

Worker::Worker(int index, GameMaster *master)
{
    this->master = master;
    this->index = index;
}

void Worker::main_loop()
{
    //mvprintw((index + 1)*2, 20, "Tutaj jestem: %d", index);
    while(!master->getEnd())
    {
        //mvprintw((index + 1)*2, 40, "Pętla: %d", index);
        this_thread::sleep_for(chrono::milliseconds((index + 1) * 10));
    }
}
