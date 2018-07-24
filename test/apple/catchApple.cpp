#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>
using namespace std;

#include "ApiAccess.cpp"
#include "unistd.h" // sleepで使う

// move2() の方向
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

void mvcursor(char num_move, WINDOW *win);
void addapple();

int terx, tery; // 現在のターミナルの幅と高さ
int have_apple; // 獲得したリンゴの数

// ユーザー名 
const int TEXT_LENGTH = 40;
char user_name[TEXT_LENGTH];

class Body
{
  public:
    double pX, pY;
    shared_ptr<Body> body = nullptr;

  Body(double x, double y) : pX(x), pY(y)
  {
  }

  void addBody()
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

  void bodyMove(double x, double y)
  {
    mvaddch(pY, pX, ' '); // 文字の移動(old)
    mvaddch(y, x, 'o'); // 文字の移動(new)

    if (body != nullptr)
      this -> body -> bodyMove(pX, pY);

    pX = x; pY = y;

  }

  bool isTouch(double x, double y)
  {
    bool touch = (x == pX && y == pY);

    if (body != nullptr)
      return touch || body -> isTouch(x, y);
    return touch;
  }
};


/* *** ヘビの体の1パーツを扱うクラス *** */
class MyCursor
{
  public:
    double myX; // x座標
    double myY; // y座標
    char myobject = '@'; // 出力する文字
    shared_ptr<Body> body = nullptr;
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

  bool checkTouchBody()
  {
    return body != nullptr && body -> isTouch(myX, myY);
  }

  /* *** 移動2 *** */
  void move2(int udlr)
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
      // default:   
    }

    if (checkTouchWall() || checkTouchBody())
    {
      clear();
      
      timeout(-1);
      
      double x = terx / 2 - 30;
      double y = tery / 2 - 5;

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
      api.postScore(user_name, have_apple);

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
      printw("POINT: %d", have_apple);

      getch();
      clear();
      refresh();
      exit(0);

    }

    mvaddch(myY, myX, myobject); // 文字の移動(new)

    if (body != nullptr)
      this -> body -> bodyMove(pX, pY);

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

  void addBody()
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
};



/* *** リンゴをあつかうクラス *** */
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

  // タイトル
  // --------------------------------------------------------------
  timeout(-1); // ブロッキングモード
  curs_set(1); // カーソルの見え方 : 透過
  echo();

  while(true){

    const int RANKING_START_Y = tery / 2 - 5;
    const int RANKING_START_X = terx / 2 - 40;
    int loop_counter = 0;

    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|-----------------------------------------------------------------------------|");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|                                                                             |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|    #####                                   #####                            |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|   #     #  #    #    ##    #    #  ###### #     #    ##    #    #  ######   |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|   #        ##   #   #  #   #   #   #      #         #  #   ##  ##  #        |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|    #####   # #  #  #    #  ####    #####  #  ####  #    #  # ## #  #####    |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|         #  #  # #  ######  #  #    #      #     #  ######  #    #  #        |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|   #     #  #   ##  #    #  #   #   #      #     #  #    #  #    #  #        |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|    #####   #    #  #    #  #    #  ######  #####   #    #  #    #  ######   |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|                                                                             |");
    loop_counter++;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "|-----------------------------------------------------------------------------|");
    loop_counter+=2;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "+ Please input the user-name and press the [Enter] ");
    loop_counter+=2;
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "+ UserName: [                                         ]");

    // 入力の受付
    move(RANKING_START_Y+loop_counter, RANKING_START_X+13);
    getnstr(user_name, TEXT_LENGTH);

    // 入力値の検証
    if(strlen(user_name) < 1){ 
      continue;
    }

    // 出力 for Debug
    // mvaddstr(0, 0, user_name);
    
    clear();
    refresh();
    break;

  }
  // --------------------------------------------------------------


  // ゲーム中
  // --------------------------------------------------------------
  noecho(); // キー入力を出力せず
  cbreak(); // 1文字打ったら終わり!!
  timeout(100); // nodelay()とほぼ同義. ERRを返すまでのタイムアウト時間.
  curs_set(0); // カーソルの見え方 : 透過

  char old_key = ERR; // 前の入力キー
  char new_key = 'j'; // 次の入力キー
  have_apple = 0; // リンゴの獲得数
  
  /* *** インスタンスの作成 *** */
  MyCursor obj(0, 0);
  AppleCursor ap;

  ap.pop_apple(); // 林檎の出現

  while (true)
  {
    new_key = getch(); // キー入力
    bool check_old_key = false;
    check_old_key = (old_key == 'j' && new_key == 'k' ||
                     old_key == 'k' && new_key == 'j' ||
                     old_key == 'h' && new_key == 'l' ||
                     old_key == 'l' && new_key == 'h');
            
    // obj.myobject = new_key; // Debug :: 入力キーをカーソルに

    /* *** キー入力なし or 入力キーが同一 *** */
    if(new_key == ERR || new_key == old_key || check_old_key) {

      obj.mycursor(old_key);

    /* *** それ以外 *** */
    }else{

      /* *** 有効なキーが押された場合 *** */
      if(obj.mycursor(new_key))
      { 
        old_key = new_key;
      }

    }

    /* *** 衝突時の動作 *** */
    if (obj.isTouching(ap))
    {
      have_apple++; // 獲得したリンゴの数+1
      ap.pop_apple(); // 新しいリンゴ
      obj.move(obj.myX, obj.myY);
      obj.addBody();
     
      /* *** 得点の表示 *** */
      const int point_status_x = 0; // 描画位置x
      const int point_status_y = tery-1; // 描画位置y
      string tmp         = "POINT: " + to_string(have_apple); // String定義
      char *point_status = new char[tmp.length()+1]; // Char配列の定義
      strcpy(point_status, tmp.c_str()); // String -> Char
      mvaddstr(point_status_y, point_status_x, point_status); // 描画
    }

    usleep(10000); // 遅延
    refresh(); // 更新

  }

  endwin();
}
