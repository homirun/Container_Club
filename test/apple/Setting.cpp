#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>
using namespace std;

#include "Setting.hpp"
#include "ApiAccess.cpp"
#include "unistd.h"


Setting::Setting()
{
  /* *** おまじない *** */
  WINDOW *w = initscr(); // スクリーンの生成
  int y, x;
  getmaxyx(w, y, x); // 最大の枠サイズ

  terX = x;
  terY = y;

  // タイトル
  // --------------------------------------------------------------
  timeout(-1); // ブロッキングモード
  curs_set(1); // カーソルの見え方 : 透過
  echo();
}

int Setting::terX;
int Setting::terY;
int Setting::have_apple = 0;
