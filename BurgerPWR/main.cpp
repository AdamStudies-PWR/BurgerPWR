#include <iostream>
#include <interface.h>
#include <ncurses.h>

using namespace std;

int main()
{
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  if(has_colors())
  {
      start_color();
      keypad(stdscr, true);
      new Interface();
  }
  else
  {
    cout<<"Ta konsola nie obsługuje kolorów"<<endl;
    getch();
  }
  endwin();
  return 0;
}
