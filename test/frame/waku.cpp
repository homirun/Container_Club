#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
using namespace std;

void waku()
{
  initscr();
  int mx, my;
  getmaxyx(stdscr, my, mx);

  cout << "[0;0H";

  for (int i = 0; i < my - 1; i++)
  {
    for (int j = 0; j < mx; j++)
    {
      if (i == 0 && j == 0)
        cout << "╭";

      else if (i == 0 && j == mx - 1)
        cout << "╮";

      else if (i == my - 2&& j == 0)
        cout << "╰";

      else if (i == my - 2 && j == mx - 1)
        cout << "╯";


      else if (i == 0 || i == my - 2)
        cout << "─";

      else if (j == 0 || j == mx - 1)
        cout << "│";

      else
        cout << " ";

      if (j == mx)
        cout << endl;
    }
  }
  int a;
  cin >> a;

  refresh();
  curs_set(0);
  endwin();

}
