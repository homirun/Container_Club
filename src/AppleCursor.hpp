#ifndef APPLECURSOR_HEADER
#define APPLECURSOR_HEADER

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

using namespace std;

class AppleCursor: public MyCursor
{
  public:
    AppleCursor();
    void pop_apple();
};

#endif

