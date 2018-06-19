#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "waku.hpp"
using namespace std;

int main()
{
  waku();

  noecho();
  // keypad(stdscr, TRUE);


  cout << "[5;5H";
  cout << "@";

  int x = 5, y = 5;

  char a;
  cin >> a;


  while(true)
  {
    cbreak();

    if (a == 'a')
    {
      x--;
      waku();
      move(x, y);
      cout << "@";
    }

    if (a == 's')
    {
      y--;
      waku();
      move(x, y);
      cout << "@";
    }

    if (a == 'd')
    {
      x++;
      waku();
      move(x, y);
      cout << "@";
    }

    if (a == 'w')
    {
      y++;
      waku();
      move(x, y);
      cout << "@";
    }

    cin >> a;

  }

}
