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

Setting::Setting()
{

}


void Setting::setStart()
{
  /* *** おまじない *** */
  WINDOW *w = initscr(); // スクリーンの生成
  int y, x;
  getmaxyx(w, y, x); // 最大の枠サイズ

  terX = x;
  terY = y;

  timeout(-1); // ブロッキングモード
  curs_set(1); // カーソルの見え方 : 透過
  echo();
}


void Setting::setGame()
{
  noecho(); // キー入力を出力せず
  cbreak(); // 1文字打ったら終わり!!
  timeout(100); // nodelay()とほぼ同義. ERRを返すまでのタイムアウト時間.
  curs_set(0); // カーソルの見え方 : 透過
}


int Setting::terX;
int Setting::terY;
int Setting::have_apple = 0;
