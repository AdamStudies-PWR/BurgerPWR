#include "graphicfunc.h"

GraphicFunc::GraphicFunc() {}

void GraphicFunc::draw_game()
{
  clear();

}

void GraphicFunc::check_size()
{
  getmaxyx(stdscr, rows, columns);
}

void GraphicFunc::print_title()
{
  attron(COLOR_PAIR(1));
  mvprintw(rows/3 - 7, columns/2 - 53, ".______    __    __  .______        _______  _______ .______      .______  ____    __    ____ .______");
  mvprintw(rows/3 - 6, columns/2 - 53, "|   _  \\  |  |  |  | |   _  \\      /  _____||   ____||   _  \\     |   _  \\ \\   \\  /  \\  /   / |   _  \\     ");
  mvprintw(rows/3 - 5, columns/2 - 53, "|  |_)  | |  |  |  | |  |_)  |    |  |  __  |  |__   |  |_)  |    |  |_)  | \\   \\/    \\/   /  |  |_)  |    ");
  mvprintw(rows/3 - 4, columns/2 - 53, "|   _  <  |  |  |  | |      /     |  | |_ | |   __|  |      /     |   ___/   \\            /   |      /     ");
  mvprintw(rows/3 - 3, columns/2 - 53, "|  |_)  | |  `--'  | |  |\\  \\----.|  |__| | |  |____ |  |\\  \\----.|  |        \\    /\\    /    |  |\\  \\----.");
  mvprintw(rows/3 - 2, columns/2 - 53, "|______/   \\______/  | _| `._____| \\______| |_______|| _| `._____|| _|         \\__/  \\__/     | _| `._____|");
  attroff(COLOR_PAIR(1));
}
