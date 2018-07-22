#include <random>
#include <ncurses.h>
#include <list>
#include "unistd.h" // sleepで使う
using namespace std;

// move2() の方向
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

void mvcursor(char num_move, WINDOW *win);
void addapple();

int terx, tery; // 現在のターミナルの幅と高さ

/* *** ヘビの体の1パーツを扱うクラス *** */
class MyCursor
{
  public:
    double myX; // x座標
    double myY; // y座標
    char myobject = '@'; // 出力する文字

  MyCursor()
  {
  }

  MyCursor(double x, double y) : myX(x), myY(y)
  {
  }

  /* *** 移動 *** */
  void move(double x, double y)
  {
    mvaddch(myY, myX, ' '); // 文字の移動(old)

    /* *** 座標系の更新 *** */
    myX = x;
    myY = y;

    mvaddch(myY, myX, myobject); // 文字の移動(new)
  }

  /* *** 壁の衝突判定 *** */
  bool checkTouchWall()
  {
    if (terx <= myX || myX < 0)
      return true;
    if (tery <= myY || myY < 0)
      return true;
    return false;
  }

  /* *** 移動2 *** */
  void move2(int udlr)
  {

    mvaddch(myY, myX, ' '); // 文字の移動(old)

    /* *** キー分岐 *** */
    switch(udlr)
    {
      case UP:     myY--;      break;
      case DOWN:   myY++;      break;
      case LEFT:   myX--;      break;
      case RIGHT:  myX++;      break;
    }

    /* *** 壁に衝突した場合 *** */
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

    mvaddch(myY, myX, myobject); // 文字の移動(new)

  }

  /* **** キー入力の分岐 *** */
  bool mycursor(char num_move)
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
  bool isTouching(MyCursor &obj)
  {
    return (myX == obj.myX && myY == obj.myY);
  }

};

/* *** ヘビのパーツを管理するクラス *** */
class CursorManage
{
  public: 
    static std::list<MyCursor> cursors; // MyCursorを保持しておくリスト
};

std::list<MyCursor> CursorManage::cursors;

/* *** リンゴをあつかうクラス *** */
class AppleCursor: public MyCursor
{
  private:

  public:
    AppleCursor(): MyCursor(0, 0)
    {
      myobject = 'A';
      pop_apple();
    }

    void pop_apple()
    {
      /* *** 乱数の生成 *** */
      random_device rnd;
      mt19937 mt(rnd());
      uniform_int_distribution<> randX(0, terx - 1);
      uniform_int_distribution<> randY(0, tery - 1);

      this -> move(randX(mt), randY(mt));
    }
    
};

int main()
{
  /* *** おまじない *** */
  WINDOW *w = initscr(); // スクリーンの生成
  getmaxyx(w, tery, terx); // 最大の枠サイズ
  noecho(); // キー入力を出力せず
  cbreak(); // 1文字打ったら終わり!!
  timeout(100); // nodelay()とほぼ同義. ERRを返すまでのタイムアウト時間.
  // timeout(-1); // ブロッキングモード
  curs_set(0); // カーソルの見え方 : 透過

  /* *** インスタンスの作成 *** */
  MyCursor snake_head(0, 0);
  AppleCursor ap;

  // ap.pop_apple(); // 林檎の出現
  snake_head.move(0,0); // カーソルの出現

  char old_key = ERR; // 前の入力キー
  char new_key = 'j'; // 次の入力キー
  int  have_apple = 0; // リンゴの獲得数
  

  //cursors[0](20, 30);
  CursorManage::cursors.push_back(snake_head);


  while (true)
  {

    new_key = getch(); // キー入力
    // snake_head.myobject = new_key; // Debug :: 入力キーをカーソルに

    /* *** キー入力なし or 入力キーが同一 *** */
    if(new_key == ERR || new_key == old_key) {

      snake_head.mycursor(old_key);

    /* *** それ以外 *** */
    }else{

      /* *** 有効なキーが押された場合 *** */
      if(snake_head.mycursor(new_key))
      { 
        old_key = new_key;
      }

    }

    /* *** リンゴを獲得した時 *** */
    if (snake_head.isTouching(ap))
    {
      have_apple++; // 獲得したリンゴの数+1
      ap.pop_apple(); // 新しいリンゴ
      snake_head.move(snake_head.myX, snake_head.myY);

      // 新しくヘビの胴体をつける
      MyCursor snake_body(10, 10);
      
      /* *** 得点の表示 *** */
      const int point_status_x  = 0; // 描画位置x
      const int point_status_y  = tery-1; // 描画位置y
      std::string tmp           = "POINT: " + std::to_string(have_apple); // String定義
      char        *point_status = new char[tmp.length()+1]; // Char配列の定義
      strcpy(point_status, tmp.c_str()); // String -> Char
      mvaddstr(point_status_y, point_status_x, point_status); // 描画
    }

    usleep(10000); // 遅延
    refresh(); // 更新

  }

  endwin();
}
