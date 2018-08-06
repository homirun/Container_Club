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
#include "Body.hpp"
#include "ApiAccess.cpp"

using namespace std;


MyCursor::MyCursor(double x, double y) : myX(x), myY(y)
{
}


/* *** 移動 *** */
void MyCursor::move(double x, double y)
{
  mvaddch(myY, myX, ' '); // 文字の移動(old)

  /* *** 座標系の更新 *** */
  myX = x;
  myY = y;

  mvaddch(myY, myX, myobject); // 文字の移動(new)
}


/* *** 壁の衝突判定 *** */
bool MyCursor::checkTouchWall()
{
  if (Setting::terX <= myX || myX < 0)
    return true;
  if (Setting::terY <= myY || myY < 0)
    return true;
  return false;
}


bool MyCursor::checkTouchBody()
{
  return body != nullptr && body -> isTouch(myX, myY);
}


/* *** 移動2 *** */
void MyCursor::move2(int udlr)
{
  double pX = myX, pY = myY;

  mvaddch(myY, myX, ' '); // 文字の移動(old)

  /* *** キー分岐 *** */
  switch(udlr)
  {
    case UP:      myY--;      break;
    case DOWN:    myY++;      break;
    case LEFT:    myX--;      break;
    case RIGHT:   myX++;      break;
  }

  if (checkTouchWall() || checkTouchBody())
  {
    this -> gameOver();
  }

  mvaddch(myY, myX, myobject); // 文字の移動(new)

  if (body != nullptr)
    this -> body -> bodyMove(pX, pY);

}

/* **** キー入力の分岐 *** */
bool MyCursor::mycursor(char num_move)
{
  if (num_move == 'h')
    this -> move2(LEFT);
  else if (num_move == 'j')
    this -> move2(DOWN);
  else if (num_move == 'k')
    this -> move2(UP);
  else if (num_move == 'l')
    this -> move2(RIGHT);
  else
    return false;
  
  return true;
}

/* *** 衝突の判定 *** */
bool MyCursor::isTouching(MyCursor &obj)
{
  return (myX == obj.myX && myY == obj.myY);
}

void MyCursor::addBody()
{
  if (body == nullptr)
  {
    body = shared_ptr <Body> (new Body(myX, myY));
  }
  else 
  {
    body -> addBody();
  }
}


void MyCursor::set_name(char *user_name)
{
  name = user_name;
}


void MyCursor::gameOver()
{
  clear();
  
  timeout(-1);
  
  double x = Setting::terX / 2 - 30;
  double y = Setting::terY / 2 - 5;

  // GameOverの文字表示
  // --------------------------------------------------------------
  move(x, y);
  printw("   mmm                                                         ");
  move(x, y + 1);
  printw(" m\"   \"  mmm   mmmmm   mmm           mmm   m   m   mmm    m mm ");
  move(x, y + 2);
  printw(" #   mm \"   #  # # #  #\"  #         #\" \"#  \"m m\"  #\"  #   #\"  \"");
  move(x, y + 3);
  printw(" #    # m\"\"\"#  # # #  #\"\"\"\"         #   #   #m#   #\"\"\"\"   #    ");
  move(x, y + 4);
  printw("  \"mmm\" \"mm\"#  # # #  \"#mm\"         \"#m#\"    #    \"#mm\"   #    ");
  move(x + 1, y + 5);
  // --------------------------------------------------------------
  
  // スコアの送信 & ランキングの表示(API系)
  // --------------------------------------------------------------
  ApiAccess api;
  vector<pair<string, int>> result(10);
  result = api.getScore();
  const int RANKING_START_Y = y+7;
  const int RANKING_START_X = (x+1)+15;
  int loop_counter = 0;
  int rank_counter = 1;

  // スコアの送信
  api.postScore(name, Setting::have_apple);

  // ランキングの表示
  
  // 枠
  mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");
  loop_counter++;
  mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "| rank  | name       | score   |");
  loop_counter++;
  mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");
  loop_counter++;

  for(auto vc : result) {

    /* *** 出力する文字列の組み立て *** */
    const int RANK_WIDTH = 5;
    string rank = api.smart_format(to_string(rank_counter), RANK_WIDTH); // 順位

    const int NAME_WIDTH = 10;
    string name = api.smart_format(vc.first, NAME_WIDTH); // 名前

    const int SCORE_WIDTH = 7;
    string score = api.smart_format(to_string(vc.second), SCORE_WIDTH); // スコア

    string text = "| " + rank + " | " + name + " | " + score + " |";

    // String -> char[]
    char *record = new char[text.length()+1]; // Char配列の定義
    strcpy(record, text.c_str()); // String -> Char

    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, record); // 描画

    loop_counter++;
    rank_counter++;
  }

  // 枠
  mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");
  loop_counter++;
  // --------------------------------------------------------------
  
  // POINT: 食べたりんごの数
  move(RANKING_START_X, RANKING_START_Y+loop_counter);
  printw("POINT: %d", Setting::have_apple);

  getch();
  clear();
  refresh();
  exit(0);
}
