#include "gamemaster.h"

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
