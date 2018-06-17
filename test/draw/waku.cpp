#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

void waku(int wx, int wy)
{
  initscr();
  int mx, my;
  getmaxyx(stdscr, my, mx);

  if (wx > mx)
    mx = wx;
  if (wy > my)
    my = wy;

  printw("Hello");

  // cout << "[0;0H";

  // for (int i = 0; i < wy - 1; i++)
  // {
  //   for (int j = 0; j < wx; j++)
  //   {
  //     if (i == 0 && j == 0)
  //       // cout << "╭";
  //
  //     else if (i == 0 && j == wx - 1)
  //       // cout << "╮";
  //
  //     else if (i == wx - 2 && j == 0)
  //       // cout << "╰";
  //
  //     else if (i == wy - 2 && j == wx - 1)
  //       // cout << "╯";
  //
  //     else if (i == 0 || i == my - 2)
  //       // cout << "─";
  //
  //     else if (j == 0 || j == wx - 1)
  //       // cout << "│";
  //
  //     else
  //       // cout << " ";
  //
  //     if (j == wx)
  //       // cout << endl;
  //
  //   }
  // }

  curs_set(0);
  refresh();
  endwin();

}
