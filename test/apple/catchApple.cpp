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

  // 移動
  void move2(int udlr) 
  {
    
    // while(true)
    for(int i=0;i<20;i++)
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
        default:     continue; break;
      } 

      // 文字の移動(new)
      mvaddch(myY, myX, myobject);

      // 更新
      usleep(100000);
      refresh();
    }
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

  move(100, 100); // 移動
 
  ap.pop_apple(); // 林檎の出現

  while (true)
  {
    // カーソル分岐
    char key_down = getch();

    // 有効な移動
    obj.mycursor(key_down);

    /* 衝突時の動作
    if (obj.isTouching(ap))
    {
      ap.pop_apple();
      obj.move(obj.myX, obj.myY);
    }*/
    
    usleep(10000); // 遅延

    refresh();
  }

  endwin();
}


// random
// random_device rnd;
// mt19937 mt(rnd());
// uniform_int_distribution<> rand100(0, 99);
// cout << rand100(mt) << endl;





// void mvcursor(char num_move, WINDOW *win)
// {
//   int x, y;
//   getyx(win, y, x);
// 
//   if (num_move == 'h' && x != 0)
//   {
//     addch(' ');
//     mvaddch(y, x - 1, '@');
//     move(y, x - 1);
//   }
//   else if (num_move == 'j')
//   {
//     addch(' ');
//     mvaddch(y + 1, x, '@');
//     move(y + 1, x);
//   }
//   else if (num_move == 'k' && y != 0)
//   {
//     addch(' ');
//     mvaddch(y - 1, x, '@');
//     move(y - 1, x);
//   }
//   else if (num_move == 'l')
//   {
//     addch(' ');
//     addch('@');
//     move(y, x + 1);
//   }
// }

// void addapple()
// {
//   int ax, ay;
// 
//   ax = 100;
//   ay = 100;
// 
//   mvaddch(ay, ax, 'A');
// }
