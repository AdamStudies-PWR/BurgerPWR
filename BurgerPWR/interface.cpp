#include "interface.h"

Interface::Interface()
{
  printw("Dopasuj rozmiar okna tak aby napis BurgerPWR był widoczny na ekranie oraz znajdował sie mniej więcej na środku ekranu");
  //int g = getch();
  //printw("%d", g);
  getch();
  check_size();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  main_menu();
}

void Interface::check_size()
{
  getmaxyx(stdscr, rows, columns);
}

void Interface::print_title()
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

void Interface::main_menu()
{
  string ch1 = selection;
  string ch2 = "  ";
  string temp;
  int input;
  do
  {
    clear();
    print_title();
    printw("\n\n\n\n\n");
    mvprintw(rows/2, columns/2 - 7, "[%s] Nowa Gra", ch1.c_str());
    mvprintw(rows/2 + 1, columns/2 - 7, "[%s] Wyjdź", ch2.c_str());
    input = getch();
    check_size();
    switch(input)
    {
       case KEY_UP:
       {
         temp = ch1;
         ch1 = ch2;
         ch2 = temp;
       } break;
       case KEY_DOWN:
       {
          temp = ch2;
          ch2 = ch1;
          ch1 = temp;
       } break;
       case 10:
       {
          if(ch2 == selection) return;
          else if(set_up()) return;
       } break;
    }
  } while (true);
}

bool Interface::set_up()
{
  string choice[] = {selection, "  ", "  ", "  ", "  ", "  "};
  string mode = "nieskończony";
  int ch = 0;
  int input;
  do
  {
    clear();
    print_title();
    printw("\n\n\n\n\n");
    mvprintw(rows/2, columns/2 - 7, "[%s] Rozpocznij", choice[0].c_str());
    mvprintw(rows/2 + 1, columns/2 - 7, "[%s] Tryb: %s", choice[1].c_str(), mode.c_str());
    mvprintw(rows/2 + 2, columns/2 - 7, "[%s] Ilość pracowników: %d", choice[2].c_str(), workers);
    mvprintw(rows/2 + 3, columns/2 - 7, "[%s] Pensja: %d zł na godzinę", choice[3].c_str(), pay);
    mvprintw(rows/2 + 4, columns/2 - 7, "[%s] Ceny", choice[4].c_str());
    mvprintw(rows/2 + 5, columns/2 - 7, "[%s] Cofnij", choice[5].c_str());
    input = getch();
    check_size();
    switch(input)
    {
       case KEY_UP:
       {
         choice[ch] = "  ";
         if(ch - 1 < 0) ch = 5;
         else ch--;
         choice[ch] = selection;
       } break;
       case KEY_DOWN:
       {
          choice[ch] = "  ";
          if(ch + 1 > 5) ch = 0;
          else ch++;
          choice[ch] = selection;
       } break;
       case KEY_LEFT:
       {
          switch(ch)
          {
            case 1:
            {
              highscore = !highscore;
              if(highscore) mode = "highscore";
              else  mode = "nieskończony";
            } break;
            case 3: if(pay - 1 > 7) pay--; break;
            case 2: if(workers - 1 > 0) workers--; break;
          }
       } break;
       case KEY_RIGHT:
       {
          switch(ch)
          {
            case 1:
            {
              highscore = !highscore;
              if(highscore) mode = "highscore";
              else  mode = "nieskończony";
            } break;
            case 3: if(pay + 1 < 25) pay++; break;
            case 2: if(workers + 1 < 7) workers++; break;
          }
       } break;
       case 10:
       {
          switch(ch)
          {
            case 0:
            {
              new GameMaster();
              return true;
            } break;
            case 4: set_prices(); break;
            case 5: return false;
          }
       } break;
    }
  } while (true);
}

void Interface::set_prices()
{
  string choice[] = {selection, "  ", "  ", "  ", "  ", "  "};
  string mode = "nieskończony";
  int ch = 0;
  int input;
  do
  {
    clear();
    print_title();
    printw("\n\n\n\n\n");
    mvprintw(rows/2, columns/2 - 7, "[%s] Burger: %d", choice[0].c_str(), prices[0]);
    mvprintw(rows/2 + 1, columns/2 - 7, "[%s] Frytki: %d", choice[1].c_str(), prices[1]);
    mvprintw(rows/2 + 2, columns/2 - 7, "[%s] Cola: %d", choice[2].c_str(), prices[2]);
    mvprintw(rows/2 + 3, columns/2 - 7, "[%s] Pizza %d:", choice[3].c_str(), prices[3]);
    mvprintw(rows/2 + 4, columns/2 - 7, "[%s] Kebab: %d", choice[4].c_str(), prices[4]);
    mvprintw(rows/2 + 5, columns/2 - 7, "[%s] Zatwierdź", choice[5].c_str());
    input = getch();
    check_size();
    switch(input)
    {
       case KEY_UP:
       {
         choice[ch] = "  ";
         if(ch - 1 < 0) ch = 5;
         else ch--;
         choice[ch] = selection;
       } break;
       case KEY_DOWN:
       {
          choice[ch] = "  ";
          if(ch + 1 > 5) ch = 0;
          else ch++;
          choice[ch] = selection;
       } break;
       case KEY_LEFT:
       {
          switch(ch)
          {
            case 0: if(prices[0] - 1 > 3) prices[0]--; break;
            case 1: if(prices[1] - 1 > 2) prices[1]--; break;
            case 2: if(prices[2] - 1 > 2) prices[2]--; break;
            case 3: if(prices[3] - 1 > 5) prices[3]--; break;
            case 4: if(prices[4] - 1 > 4) prices[4]--; break;
          }
       } break;
       case KEY_RIGHT:
       {
          switch(ch)
          {
            case 0: if(prices[0] + 1 < 17) prices[0]++; break;
            case 1: if(prices[1] + 1 < 13) prices[1]++; break;
            case 2: if(prices[2] + 1 < 13) prices[2]++; break;
            case 3: if(prices[3] + 1 < 25) prices[3]++; break;
            case 4: if(prices[4] + 1 < 21) prices[4]++; break;
          }
       } break;
       case 10:
       {
          if(ch == 5) return;
       } break;
    }
  } while (true);
}
