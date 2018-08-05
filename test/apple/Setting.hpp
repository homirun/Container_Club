#ifndef SETTING_HEADER
#define SETTING_HEADER

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>
using namespace std;

class Setting
{
  public:
    static int terX;
    static int terY;
    static int have_apple;

    Setting();
    void setStart();
};

#endif

