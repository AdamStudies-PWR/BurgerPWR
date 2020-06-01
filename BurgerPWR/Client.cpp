#include "gamemaster.h"

Client::~Client()
{
    delete master;
}

Client::Client(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3, takeaway *tk, bool *seats)
{
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
    this->master = master;
    this->index = index;
    this->tk = tk;
    this->seats = seats;
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
            case 4: take_food(); break;
            case 5: eat(); break;
            case 6: wait3(); break;
            case 7: return;
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k1->index);
        master->drawing = false;
        dlock.unlock();
    }
    else if(!k2->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->take = true;
        chosen = k2;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k2->index);
        master->drawing = false;
        dlock.unlock();
    }
    else if(!k3->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->take = true;
        chosen = k3;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k3->index);
        master->drawing = false;
        dlock.unlock();
    }
    else
    {
        state = 1;
        master->line2++;
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_line2(master->line2);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k1->index);
        master->line2--;
        master->draw_line2(master->line2);
        master->drawing = false;
        dlock.unlock();
    }
    else if(!k2->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k2->take = true;
        chosen = k2;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k2->index);
        master->line2--;
        master->draw_line2(master->line2);
        master->drawing = false;
        dlock.unlock();
    }
    else if(!k3->take)
    {
        unique_lock<mutex> locker(k1->m, defer_lock);
        locker.lock();
        state = 2;
        k3->take = true;
        chosen = k3;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_petent(k3->index);
        master->line2--;
        master->draw_line2(master->line2);
        master->drawing = false;
        dlock.unlock();
    }
}

void Client::give_order()
{
    //if(order != NULL) delete order;
    int size = (rand() % 3) + 1;
    order = new int[size + 2];
    order[0] = size + 2;
    time = 8 * size;
    osize = size;
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
    state = 3;
    locker.unlock();
    while(master->drawing) sleep();
    unique_lock<mutex> dlock(master->m, defer_lock);
    dlock.lock();
    master->drawing = true;
    master->clear_petent(chosen->index);
    master->line3++;
    master->draw_line3(master->line3);
    master->drawing = false;
    dlock.unlock();
}

void Client::wait2()
{
    if(tk->mealfor == index)
    {
        master->line3--;
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_line3(master->line3);
        master->draw_ctake();
        master->drawing = false;
        dlock.unlock();
        state = 4;
    }
}

void Client::take_food()
{
    int *temp = new int[osize];
    for(int i=0; i<8; i++)
    {
        if(!seats[i])
        {
            for(int j=0; j<osize; j++)
            {
                temp[j] = order[j + 2];
            }
            seats[i] = true;
            while(master->drawing) sleep();
            unique_lock<mutex> dlock(master->m, defer_lock);
            dlock.lock();
            master->drawing = true;
            master->draw_seat(i, temp, osize);
            master->clear_ctake();
            master->drawing = false;
            dlock.unlock();
            tk->mealfor = -1;
            state = 5;
            counter = 0;
            seat_id = i;
            delete[] temp;
            return;
        }
    }
    delete[] temp;
    master->line5++;
    while(master->drawing) sleep();
    unique_lock<mutex> dlock(master->m, defer_lock);
    dlock.lock();
    master->drawing = true;
    master->draw_line5(master->line5);
    master->drawing = false;
    dlock.unlock();
    state = 6;
}

void Client::wait3()
{
    int *temp = new int[osize];
    for(int i=0; i<8; i++)
    {
        if(!seats[i])
        {
            for(int j=0; j<osize; j++)
            {
                temp[j] = order[j + 2];
            }
            seats[i] = true;
            state = 5;
            master->line5--;
            while(master->drawing) sleep();
            unique_lock<mutex> dlock(master->m, defer_lock);
            dlock.lock();
            master->drawing = true;
            master->draw_line5(master->line5);
            master->draw_seat(i, temp, osize);
            master->drawing = false;
            dlock.unlock();
            counter = 0;
            seat_id = 3;
            delete[] temp;
            return;
        }
    }
    delete[] temp;
}

void Client::eat()
{
    float temp = 0;
    if(counter < time)
    {
        this_thread::sleep_for(chrono::seconds(1));
        counter++;
        temp = float(counter)/float(time);
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->update_seat(seat_id, temp);
        master->drawing = false;
        dlock.unlock();
    }
    else
    {
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->clear_seat(seat_id);
        master->drawing = false;
        dlock.unlock();
        state = 7;
        master->decreaseClients();
        seats[seat_id] = false;
    }
}

void Client::sleep()
{
    this_thread::sleep_for(chrono::milliseconds(10));
}

