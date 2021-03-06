#include "gamemaster.h"

Worker::~Worker()
{
    delete master;
}

Worker::Worker(int index, GameMaster *master, kasa *k1, kasa *k2, kasa *k3, kitchen *c1, kitchen *c2, kitchen *c3, kitchen *c4, kitchen *c5, kitchen *c6, kitchen *c7, kitchen *c8, takeaway *tk)
{
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
    this->master = master;
    this->index = index;
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
    this->c4 = c4;
    this->c5 = c5;
    this->c6 = c6;
    this->c7 = c7;
    this->c8 = c8;
    this->tk = tk;
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
            case 3: cook(); break;
            case 4: give_food(); break;
            case 5: end(); break;
            case 6: wait2();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->clear_cash(chosen->index);
        for(int i=0; i<(order[0]-2); i++)
        {
            master->income = master->income + master->prices[order[i + 2]];
        }
        dlock.unlock();
        master->drawing = false;
        time = 3*order[0];
        order_for = order[1];
        chosen->busy = false;
        chosen->isready = false;
        state = 3;
        counter = 0;
        locker.unlock();
        choose_cooker();
    }
}

void Worker::choose_cooker()
{
    if(!c1->busy)
    {
        unique_lock<mutex> locker(c1->m, defer_lock);
        locker.lock();
        c1->busy = true;
        locker.unlock();
        cooker = c1;
    }
    else if(!c2->busy)
    {
        unique_lock<mutex> locker(c2->m, defer_lock);
        locker.lock();
        c2->busy = true;
        locker.unlock();
        cooker = c2;
    }
    else if(!c3->busy)
    {
        unique_lock<mutex> locker(c3->m, defer_lock);
        locker.lock();
        c3->busy = true;
        locker.unlock();
        cooker = c3;
    }
    else if(!c4->busy)
    {
        unique_lock<mutex> locker(c4->m, defer_lock);
        locker.lock();
        c4->busy = true;
        locker.unlock();
        cooker = c4;
    }
    else if(!c5->busy)
    {
        unique_lock<mutex> locker(c5->m, defer_lock);
        locker.lock();
        c5->busy = true;
        locker.unlock();
        cooker = c5;
    }
    else if(!c6->busy)
    {
        unique_lock<mutex> locker(c6->m, defer_lock);
        locker.lock();
        c6->busy = true;
        locker.unlock();
        cooker = c6;
    }
    else if(!c7->busy)
    {
        unique_lock<mutex> locker(c7->m, defer_lock);
        locker.lock();
        c7->busy = true;
        locker.unlock();
        cooker = c7;
    }
    else
    {
        unique_lock<mutex> locker(c8->m, defer_lock);
        locker.lock();
        c8->busy = true;
        locker.unlock();
        cooker = c8;
    }
    while(master->drawing) sleep();
    unique_lock<mutex> dlock(master->m, defer_lock);
    dlock.lock();
    master->drawing = true;
    master->draw_cook(cooker->index);
    master->drawing = false;
    dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k1->index);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k2->index);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k3->index);
        master->drawing = false;
        dlock.unlock();
    }
    else
    {
        state = 1;
        master->line++;
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_line(master->line);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k1->index);
        master->line--;
        master->draw_line(master->line);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k2->index);
        master->line--;
        master->draw_line(master->line);
        master->drawing = false;
        dlock.unlock();
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
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_cash(k3->index);
        master->line--;
        master->draw_line(master->line);
        master->drawing = false;
        dlock.unlock();
    }
}

void Worker::cook()
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
        master->update_cook(cooker->index, temp);
        master->drawing = false;
        dlock.unlock();
    }
    else
    {
        unique_lock<mutex> locker(cooker->m, defer_lock);
        locker.lock();
        cooker->busy = false;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->clear_cook(cooker->index);        
        master->drawing = false;
        dlock.unlock();
        state = 4;
    }
}

void Worker::give_food()
{
    if(!tk->busy)
    {
        unique_lock<mutex> locker(tk->m, defer_lock);
        locker.lock();
        tk->busy = true;
        tk->mealfor = order_for;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_take();
        master->drawing = false;
        dlock.unlock();
        state = 5;
    }
    else
    {
        state = 6;
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->line4++;
        master->draw_line4(master->line4);
        master->drawing = false;
        dlock.unlock();
    }
}

void Worker::wait2()
{
    if(!tk->busy)
    {
        unique_lock<mutex> locker(tk->m, defer_lock);
        locker.lock();
        tk->busy = true;
        tk->mealfor = order_for;
        locker.unlock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->draw_take();
        master->line4--;
        master->draw_line4(master->line4);
        master->drawing = false;
        dlock.unlock();
        state = 5;
    }
}

void Worker::end()
{
    if(tk->mealfor == -1)
    {
        unique_lock<mutex> locker(tk->m, defer_lock);
        locker.lock();
        while(master->drawing) sleep();
        unique_lock<mutex> dlock(master->m, defer_lock);
        dlock.lock();
        master->drawing = true;
        master->clear_take();
        master->drawing = false;
        dlock.unlock();
        tk->busy = false;
        locker.unlock();
        state = 0;
    }
}

void Worker::sleep()
{
    this_thread::sleep_for(chrono::milliseconds(10));
}
