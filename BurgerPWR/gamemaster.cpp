#include "gamemaster.h"

GameMaster::GameMaster() {}

GameMaster::GameMaster(bool mode, int prices[], int cost[], int pay, int max_workers)
{
  k1 = new kasa(1);
  k2 = new kasa(2);
  k3 = new kasa(3);
  for(int i=0; i<5; i++)
  {
    this->prices[i] = prices[i];
    this->cost[i] = cost[i];
  }
  this->pay = pay;
  this->max_workers = max_workers;
  draw_game();
  side_UI();
  nodelay(stdscr, true);
  for(int i=0; i<max_workers; i++)
  {
      Worker *w = new Worker(i, this, k1, k2, k3);
      workers.emplace_back(&Worker::main_loop, w);
  }
  for(int i=0; i<max_workers; i++) workers[i].detach();
  thread keyboard(&GameMaster::check_keyboard, this);
  keyboard.detach();
  main_loop();
}

GameMaster::~GameMaster()
{
    end = true;
    delete k1;
    delete k2;
    delete k3;
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
  budget = budget - loss + income;
  income = 0;
}

void GameMaster::main_loop()
{
  int randw;
  while(!end)
  {
    this_thread::sleep_for(chrono::milliseconds(1000));
    refresh_bar();
    attron(COLOR_PAIR(INFO_BAR));
    mvprintw(0, 0, "Dzień: %d%d%d%d   Czas: %d%d:%d%d", day[0], day[1], day[2], day[3], hour[0], hour[1], minutes[0], minutes[1]);
    mvprintw(rows - 1, 0, "Przychód: %d$ \t\t Straty: %d$", income, loss);
    mvprintw(rows - 1, columns - 20, "Budżet: %d$", budget);
    calculate_cost();
    timer();
    if(clients < max_clients)
    {
        randw = rand() % 5;
        if(randw == 1) start_client();
    }
    attroff(COLOR_PAIR(INFO_BAR));
  }
}

void GameMaster::start_client()
{
    clients++;
    Client *c = new Client(history, this, k1, k2, k3);
    history++;
    thread cli(&Client::main_loop, c);
    cli.detach();
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

Worker::Worker(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3)
{
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
    this->master = master;
    this->index = index;
}

void Worker::main_loop()
{
    while(!master->getEnd())
    {
        switch(state)
        {
            case 0: begin(); break;
            case 1: wait(); break;
            case 2: take_order(); break;
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void Worker::take_order()
{
    if(chosen->isready)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        order = chosen->order;
        master->clear_cash(chosen->index);
        time = 2*order[0];
        chosen->busy = false;
        state = 3;
        locker.unlock();
    }
}

void Worker::begin()
{
    if(!k1->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k1->busy = true;
        k1->take = false;
        chosen = k1;
        locker.unlock();
        master->draw_cash(k1->index);
    }
    else if(!k2->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->busy = true;
        k2->take = false;
        chosen = k2;
        locker.unlock();
        master->draw_cash(k2->index);
    }
    else if(!k3->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->busy = true;
        k3->take = false;
        chosen = k3;
        locker.unlock();
        master->draw_cash(k3->index);
    }
    else
    {
        state = 1;
        master->line++;
        master->draw_line(master->line);
    }
}

void Worker::wait()
{
    if(!k1->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k1->busy = true;
        k1->take = false;
        chosen = k1;
        locker.unlock();
        master->draw_cash(k1->index);
        master->line--;
        master->draw_line(master->line);
    }
    else if(!k2->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->busy = true;
        k2->take = false;
        chosen = k2;
        locker.unlock();
        master->draw_cash(k2->index);
        master->line--;
        master->draw_line(master->line);
    }
    else if(!k3->busy)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->busy = true;
        k3->take = false;
        chosen = k3;
        locker.unlock();
        master->draw_cash(k3->index);
        master->line--;
        master->draw_line(master->line);
    }
}

Client::~Client()
{
    delete master;
}

Client::Client(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3)
{
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
    this->master = master;
    this->index = index;
}

void Client::main_loop()
{
    while(!master->getEnd())
    {
        switch(state)
        {
            case 0: begin(); break;
            case 1: wait(); break;
            case 2: give_order(); break;
            case 3: wait2(); break;
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void Client::begin()
{
    if(!k1->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k1->take = true;
        chosen = k1;
        locker.unlock();
        master->draw_petent(k1->index);
    }
    else if(!k2->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->take = true;
        chosen = k2;
        locker.unlock();
        master->draw_petent(k2->index);
    }
    else if(!k3->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->take = true;
        chosen = k3;
        locker.unlock();
        master->draw_petent(k3->index);
    }
    else
    {
        state = 1;
        master->line2++;
        master->draw_line2(master->line2);
    }
}

void Client::wait()
{
    if(!k1->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k1->take = true;
        chosen = k1;
        locker.unlock();
        master->draw_petent(k1->index);
        master->line2--;
        master->draw_line(master->line2);
    }
    else if(!k2->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->take = true;
        chosen = k2;
        locker.unlock();
        master->draw_petent(k2->index);
        master->line2--;
        master->draw_line(master->line2);
    }
    else if(!k3->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->take = true;
        chosen = k3;
        locker.unlock();
        master->draw_petent(k3->index);
        master->line2--;
        master->draw_line(master->line2);
    }
}

void Client::give_order()
{
    //if(order != NULL) delete order;
    int size = (rand() % 3) + 1;
    order = new int[size + 2];
    order[0] = size + 2;
    order[1] = index;
    for(int i=0; i<size; i++)
    {
        order[i + 2] = (rand() % 5);
    }
    unique_lock<mutex> locker(k1->m, defer_lock);
    locker.lock();
    chosen->order = order;
    chosen->isready = true;
    chosen->payed = false;
    master->clear_petent(chosen->index);
    state = 3;
    locker.unlock();
    master->line3++;
    master->draw_line3(master->line3);
}

void Client::wait2()
{

}
