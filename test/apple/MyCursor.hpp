#ifndef MYCURSOR_HEADER
#define MYCURSOR_HEADER

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

#include "Setting.hpp"
#include "Body.hpp"
#include "ApiAccess.cpp"

// move2() の方向
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

using namespace std;

class MyCursor
{
  public:
    double myX; // x座標
    double myY; // y座標
    char myobject = '@'; // 出力する文字
    char *name;
    shared_ptr<Body> body = nullptr;

    MyCursor(double x, double y);

    void move(double x, double y);
    bool checkTouchWall();
    bool checkTouchBody();
    void move2(int udlr);
    bool mycursor(char num_move);
    bool isTouching(MyCursor &obj);
    void addBody();
    void gameOver();
    void set_name(char *user_name);
};

#endif

