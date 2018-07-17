#include <random>
#include <ncurses.h>
using namespace std;

// sleepで使う
#include "unistd.h"

// move2() の方向
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

void mvcursor(char num_move, WINDOW *win);
void addapple();

int terx, tery;

class MyCursor
{
  public:
    double myX; // x座標
    double myY; // y座標
    char myobject = '@'; // 出力する文字

  MyCursor(double x, double y) : myX(x), myY(y)
  {
  }

  // 移動
  void move(double x, double y)
  {
    // 文字の移動(old)
    mvaddch(myY, myX, ' ');

    // 座標系の更新
    myX = x;
    myY = y;

    // 文字の移動(new)
    mvaddch(myY, myX, myobject);
  }

  // 壁の衝突判定
  bool checkTouchWall()
  {
    if (terx <= myX || myX < 0)
      return true;
    if (tery <= myY || myY < 0)
      return true;
    return false;
  }

  // 移動
  void move2(int udlr)
  {

    // 文字の移動(old)
    mvaddch(myY, myX, ' ');

    // キー分岐
    switch(udlr)
    {
      case UP:     myY--;      break;
      case DOWN:   myY++;      break;
      case LEFT:   myX--;      break;
      case RIGHT:  myX++;      break;
      // default:     continue; break;
    }

    // 壁に衝突した場合
    if (checkTouchWall())
    {
      switch(udlr)
      {
        case UP:     myY++;      break;
        case DOWN:   myY--;      break;
        case LEFT:   myX++;      break;
        case RIGHT:  myX--;      break;
      }
    }

    // 文字の移動(new)
    mvaddch(myY, myX, myobject);

  }

  // キー入力の分岐
  void mycursor(char num_move)
  {
    if (num_move == 'h')
      // this -> move(myX - 1, myY);
      this -> move2(LEFT);
    else if (num_move == 'j')
      // this -> move(myX, myY + 1);
      this -> move2(DOWN);
    else if (num_move == 'k')
      // this -> move(myX, myY - 1);
      this -> move2(UP);
    else if (num_move == 'l')
      // this -> move(myX + 1, myY);
      this -> move2(RIGHT);
    else
      // this -> move2(BEFORE_ANGLE);
      return;
  }

  // 衝突判定
  bool isTouching(MyCursor &obj)
  {
    return (myX == obj.myX && myY == obj.myY);
  }

};

class AppleCursor: public MyCursor
{
  private:

  public:
    AppleCursor(): MyCursor(0, 0)
    {
      myobject = 'A';
    }

    void pop_apple()
    {
      // 乱数の生成
      random_device rnd;
      mt19937 mt(rnd());
      uniform_int_distribution<> randX(0, terx - 1);
      uniform_int_distribution<> randY(0, tery - 1);

      this -> move(randX(mt), randY(mt));
    }

};

int main()
{
  /* ********** おまじない ********** */
  WINDOW *w = initscr(); // スクリーンの生成
  getmaxyx(w, tery, terx); // 最大の枠サイズ
  noecho(); // キー入力を出力せず
  cbreak(); // 1文字打ったら終わり!!
  timeout(200); // nodelay()とほぼ同義. ERRを返すまでのタイムアウト時間.
  // timeout(-1); // ブロッキングモード
  curs_set(0); // カーソルの見え方 : 透過

  // インスタンスの作成
  MyCursor obj(0, 0);
  AppleCursor ap;

  ap.pop_apple(); // 林檎の出現

  char old_key = ERR; // 前の入力キー
  char new_key = 'j'; // 次の入力キー

  while (true)
  {

    new_key = getch(); // キー入力
    // obj.myobject = new_key; // Debug :: 入力キーをカーソルに

    // キー入力なし or 入力キーが同一
    if(new_key == ERR || new_key == old_key) {
      obj.mycursor(old_key);

    // それ以外
    }else{
      obj.mycursor(new_key);
      old_key = new_key;
    }

    // 衝突時の動作
    if (obj.isTouching(ap))
    {
      ap.pop_apple();
      obj.move(obj.myX, obj.myY);
    }

    usleep(10000); // 遅延
    refresh(); // 更新

  }

  endwin();
}
