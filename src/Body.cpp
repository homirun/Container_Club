#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

#include "Body.hpp"

using namespace std;

Body::Body(double x, double y) : pX(x), pY(y)
{

}


/* *** 胴体の生成 *** */
void Body::addBody()
{
  if (body == nullptr)
  {
    body = shared_ptr <Body> (new Body(pX, pY));
  }
  else
  {
    body -> addBody();
  }
}


/* *** 胴体の移動 *** */
void Body::bodyMove(double x, double y)
{
  mvaddch(pY, pX, ' '); // 文字の移動(old)
  mvaddch(y, x, 'o'); // 文字の移動(new)

  if (body != nullptr)
    this -> body -> bodyMove(pX, pY);

  pX = x; pY = y;

}


/* *** 胴体のとの接触判定 *** */
bool Body::isTouch(double x, double y)
{
  bool touch = (x == pX && y == pY);

  if (body != nullptr)
    return touch || body -> isTouch(x, y);
  return touch;
}
