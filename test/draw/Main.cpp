#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "waku.h"
using namespace std;

int main()
{
  int x = 100, y = 100;
  waku(x, y);
  // initscr();
  // int mx, my;
  // getmaxyx(stdscr, my, mx);
  //
  // cout << mx << endl;
  // cout << my << endl;
  //
  // cout << "[0;0H";
  //
  // for (int i = 0; i < my - 1; i++)
  // {
  //   for (int j = 0; j < mx; j++)
  //   {
  //     if (i == 0 && j == 0)
  //       cout << "╭";
  //
  //     else if (i == 0 && j == mx - 1)
  //       cout << "╮";
  //     else if (i == my - 2 && j == 0)
  //       cout << "╰";
  //
  //     else if (i == my - 2 && j == mx - 1)
  //       cout << "╯";
  //
  //
  //     else if (i == 0 || i == my - 2)
  //       cout << "─";
  //
  //     else if (j == 0 || j == mx - 1)
  //       cout << "│";
  //
  //     else
  //       cout << " ";
  //
  //     if (j == mx)
  //       cout << endl;
  //   }
  // }
  //
  // int x;
  // cin >> x;
  //
  // curs_set(0);
  // refresh();
  // endwin();
}
