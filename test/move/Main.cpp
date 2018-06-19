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

}
