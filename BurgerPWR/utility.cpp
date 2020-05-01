#include "utility.h"

Utility::Utility()
{
  init_pair(TITLE, COLOR_RED, COLOR_BLACK);
  init_pair(INFO_BAR, COLOR_WHITE, COLOR_RED);
  init_pair(RESTAURANT, COLOR_GREEN, COLOR_YELLOW);
  init_pair(REGISTER, COLOR_RED, COLOR_YELLOW);
  init_pair(SIT, COLOR_BLACK, COLOR_YELLOW);
  init_pair(WINDOW, COLOR_RED, COLOR_WHITE);
  init_pair(THREADS, COLOR_BLACK, COLOR_WHITE);
}

void Utility::refresh_bar()
{
  attron(COLOR_PAIR(INFO_BAR));
  for(int i=0; i<columns; i++)
  {
    mvprintw(rows - 1, i, " ");
  }
  attroff(COLOR_PAIR(INFO_BAR));
}

void Utility::draw_game()
{
  clear();
  check_size();
  attron(COLOR_PAIR(INFO_BAR));
  for(int i=0; i<columns; i++)
  {
    mvprintw(0, i, " ");
    mvprintw(rows - 1, i, " ");
  }
  mvprintw(0, columns - 24, "Naciśnij F10 aby wyjść");
  attroff(COLOR_PAIR(INFO_BAR));
  attron(COLOR_PAIR(RESTAURANT));
  //Sciany budynku
  for(int i = 1; i < (rows - 1); i++)
  {
    mvprintw(i, 0.1*columns, " ");
  }
  for(int i = 1; i < 1.4*(rows/3); i++)
  {
    mvprintw(i, 0.5*columns, " ");
  }
  for(int i = 1.6*(rows/3); i < (2*(rows/3) + 0.15*rows); i++)
  {
    mvprintw(i, 0.5*columns, " ");
  }
  for(int i = 1; i < 0.8*(rows/3); i++)
  {
    mvprintw(i, 0.7*columns, " ");
  }
  for(int i = 1.2*(rows/3); i < (rows - 1); i++)
  {
    mvprintw(i, 0.7*columns, " ");
  }
  for(int i = 0.1*columns; i < 0.52*columns; i++)
  {
    mvprintw(2*(rows/3), i, " ");
  }
  for(int i = 0.52*columns; i<0.55*columns; i++)
  {
      mvprintw(2*(rows/3), i, "^");
  }
  for(int i = 0.55*columns; i < 0.7*columns; i++)
  {
    mvprintw((2*(rows/3) + 0.15*rows), i, " ");
  }
  attroff(COLOR_PAIR(RESTAURANT));
  attron(COLOR_PAIR(SIT));
  //Siedzenia
  for(int i = 0.1*columns; i<0.15*columns; i++)
  {
      mvprintw(0.4*(rows/3), i, " ");
      mvprintw(0.8*(rows/3), i, " ");
      mvprintw(1.2*(rows/3), i, " ");
      mvprintw(1.6*(rows/3), i, " ");
  }
  for(int i = 0.45*columns; i<0.5*columns; i++)
  {
      mvprintw(0.4*(rows/3), i, " ");
      mvprintw(0.8*(rows/3), i, " ");
      mvprintw(1.2*(rows/3), i, " ");
  }
  for(int i = 0.275*columns; i<0.325*columns; i++)
  {
      mvprintw(rows/3, i, " ");
  }
  attroff(COLOR_PAIR(SIT));
  attron(COLOR_PAIR(REGISTER));
  //Kasa
  for(int i = 0.55*columns; i<0.57*columns; i++)
  {
      mvprintw(2*(rows/3), i, " ");
  }
  for(int i = 0.57*columns; i<0.6*columns; i++)
  {
      mvprintw(2*(rows/3), i, "v");
  }
  for(int i = 0.6*columns; i<0.61*columns; i++)
  {
      mvprintw(2*(rows/3), i, " ");
  }
  for(int i = 0.61*columns; i<0.64*columns; i++)
  {
      mvprintw(2*(rows/3), i, "v");
  }
  for(int i = 0.64*columns; i<0.65*columns; i++)
  {
      mvprintw(2*(rows/3), i, " ");
  }
  for(int i = 0.65*columns; i<0.68*columns; i++)
  {
      mvprintw(2*(rows/3), i, "v");
  }
  for(int i = 0.68*columns; i<0.7*columns; i++)
  {
      mvprintw(2*(rows/3), i, " ");
  }
  //Kuchnia
  for(int i = 0.15*columns; i<0.25*columns; i++)
  {
      mvprintw((2*(rows/3) + (rows/3)/3), i, "^");
      mvprintw((2*(rows/3) + 2*((rows/3)/3)), i, "^");
  }
  for(int i = 0.35*columns; i<0.45*columns; i++)
  {
      mvprintw((2*(rows/3) + (rows/3)/3), i, "^");
      mvprintw((2*(rows/3) + 2*((rows/3)/3)), i, "^");
  }
  attroff(COLOR_PAIR(REGISTER));
  attron(COLOR_PAIR(WINDOW));
  for(int i = 0.8*columns; i<(columns-2); i++)
  {
    for(int j = 2; j<(rows-2); j++)
    {
      mvprintw(j, i, " ");
    }
  }
  for(int i = ((0.8*columns) + 1); i<(columns-3); i++)
  {
      mvprintw(3, i, "-");
  }
  for(int i = ((0.8*columns) + 1); i<(columns-3); i++)
  {
      mvprintw(12, i, "-");
  }
  for(int i = ((0.8*columns) + 1); i<(columns-3); i++)
  {
      mvprintw(18, i, "-");
  }
  mvprintw(4, 0.89*columns, "Menu");
  mvprintw(13, 0.88*columns, "Pracownicy");
  mvprintw(19, 0.89*columns, "Legenda");
  mvprintw(21, 0.86*columns, "Pracownicy:");
  mvprintw(22, 0.86*columns, "Klienci:");
  attroff(COLOR_PAIR(WINDOW));
  attron(COLOR_PAIR(THREADS));
  mvprintw(21, 0.93*columns, "%s", objects[0].c_str());
  mvprintw(22, 0.93*columns, "%s", objects[1].c_str());
  attroff(COLOR_PAIR(THREADS));
}

void Utility::check_size()
{
  getmaxyx(stdscr, rows, columns);
}

void Utility::print_title()
{
  attron(COLOR_PAIR(TITLE));
  mvprintw(rows/3 - 7, columns/2 - 53, ".______    __    __  .______        _______  _______ .______      .______  ____    __    ____ .______");
  mvprintw(rows/3 - 6, columns/2 - 53, "|   _  \\  |  |  |  | |   _  \\      /  _____||   ____||   _  \\     |   _  \\ \\   \\  /  \\  /   / |   _  \\     ");
  mvprintw(rows/3 - 5, columns/2 - 53, "|  |_)  | |  |  |  | |  |_)  |    |  |  __  |  |__   |  |_)  |    |  |_)  | \\   \\/    \\/   /  |  |_)  |    ");
  mvprintw(rows/3 - 4, columns/2 - 53, "|   _  <  |  |  |  | |      /     |  | |_ | |   __|  |      /     |   ___/   \\            /   |      /     ");
  mvprintw(rows/3 - 3, columns/2 - 53, "|  |_)  | |  `--'  | |  |\\  \\----.|  |__| | |  |____ |  |\\  \\----.|  |        \\    /\\    /    |  |\\  \\----.");
  mvprintw(rows/3 - 2, columns/2 - 53, "|______/   \\______/  | _| `._____| \\______| |_______|| _| `._____|| _|         \\__/  \\__/     | _| `._____|");
  attroff(COLOR_PAIR(TITLE));
}
