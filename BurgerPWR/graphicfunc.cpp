#include "graphicfunc.h"

GraphicFunc::GraphicFunc()
{
  init_pair(TITLE, COLOR_RED, COLOR_BLACK);
  init_pair(INFO_BAR, COLOR_WHITE, COLOR_RED);
}

void GraphicFunc::draw_game()
{
  clear();
  check_size();
  attron(COLOR_PAIR(INFO_BAR));
  for(int i=0; i<columns; i++)
  {
    mvprintw(1, i, " ");
    mvprintw(rows - 1, i, " ");
  }
  attroff(COLOR_PAIR(INFO_BAR));
}

void GraphicFunc::check_size()
{
  getmaxyx(stdscr, rows, columns);
}

void GraphicFunc::print_title()
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
