#ifndef BODY_HEADER
#define BODY_HEADER

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>
using namespace std;

class Body
{
  public:
    double pX, pY;
    shared_ptr<Body> body = nullptr;

    Body(double x, double y);
    void addBody();
    void bodyMove(double x, double y);
    bool isTouch(double x, double y);
};

#endif

