#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

#include "Setting.hpp"
#include "MyCursor.hpp"
#include "AppleCursor.hpp"

using namespace std;

/* *** リンゴをあつかうクラス *** */
AppleCursor::AppleCursor(): MyCursor(0, 0)
{
  myobject = 'A';
}

void AppleCursor::pop_apple()
{
  /* *** 乱数の生成 *** */
  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> randX(0, Setting::terX - 1);
  uniform_int_distribution<> randY(0, Setting::terY - 1);

  this -> move(randX(mt), randY(mt));
}
