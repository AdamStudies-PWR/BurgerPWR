#include "interface.h"
#include "pthread.h"
#include "ncurses.h"

Interface::Interface()
{
  check_size();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  main_menu();
}

void Interface::check_size()
{
  getmaxyx(stdscr, rows, columns);
}

void Interface::main_menu()
{
  char input;
  do
  {
    clear();
    attron( A_BOLD | COLOR_PAIR(1));
    mvprintw(rows/4, columns/2 - 8, "🍔 BurgerPWR 🍔");
    attroff( A_BOLD | COLOR_PAIR(1));
    input = getch();
    check_size();
  } while (input != '0');
}
