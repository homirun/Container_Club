#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

#include "Setting.hpp"
#include "Title.hpp"
#include "ApiAccess.cpp"
#include "Body.hpp"
#include "MyCursor.hpp"
#include "unistd.h" // sleepで使う

using namespace std;

void mvcursor(char num_move, WINDOW *win);
void addapple();

// ユーザー名 
const int TEXT_LENGTH = 40;
char user_name[TEXT_LENGTH];


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
      uniform_int_distribution<> randX(0, Setting::terX - 1);
      uniform_int_distribution<> randY(0, Setting::terY - 1);

      this -> move(randX(mt), randY(mt));
    }

};

Setting setting;
Title title;

int main()
{
  setting.setStart();
  title.popTitle(user_name, TEXT_LENGTH);

  setting.setGame();

  char old_key = ERR; // 前の入力キー
  char new_key = 'j'; // 次の入力キー
  
  /* *** インスタンスの作成 *** */
  MyCursor obj(0, 0);
  AppleCursor ap;

  obj.set_name(user_name);
  ap.pop_apple(); // 林檎の出現

  while (true)
  {
    new_key = getch(); // キー入力
    bool check_old_key = false;
    check_old_key = ((old_key == 'j' && new_key == 'k') ||
                     (old_key == 'k' && new_key == 'j') ||
                     (old_key == 'h' && new_key == 'l') ||
                     (old_key == 'l' && new_key == 'h'));
            
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
      Setting::have_apple++; // 獲得したリンゴの数+1
      ap.pop_apple(); // 新しいリンゴ
      obj.move(obj.myX, obj.myY);
      obj.addBody();
     
      /* *** 得点の表示 *** */
      const int point_status_x = 0; // 描画位置x
      const int point_status_y = Setting::terY - 1; // 描画位置y
      string tmp         = "POINT: " + to_string(Setting::have_apple); // String定義
      char *point_status = new char[tmp.length()+1]; // Char配列の定義
      strcpy(point_status, tmp.c_str()); // String -> Char
      mvaddstr(point_status_y, point_status_x, point_status); // 描画
    }

    usleep(10000); // 遅延
    refresh(); // 更新

  }

  endwin();
}
