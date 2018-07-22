#include <iostream>
#include <ncurses.h>
using namespace std;
#include "unistd.h" // sleepで使う
#include "../ApiAccess.cpp"

int terx, tery;

// 空白を埋める(引数の数だけスペースを返す)
std::string smart_format(std::string str, int column_width){

  int str_len = str.length();
  int need_spaces = column_width - str_len;
  
  if(need_spaces < 0){
    return "\0";
  }
  
  std::string tmp;
  for(int i=0; i<need_spaces; i++){
    tmp += " ";
  }
  
  return str + tmp;
}

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

  /* *** 順位データの取得 *** */
  ApiAccess api;
  map<string, int> result = api.getScore();

  while(true){

    const int RANKING_START_Y = 5;
    const int RANKING_START_X = 10;
    int loop_counter = 0;
    int rank_counter = 1;

    // 枠
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");
    loop_counter++;

    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "| rank  | name       | score   |");
    loop_counter++;

    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");
    loop_counter++;

    for(auto mp : result) {
      
      /* *** 出力する文字列の組み立て *** */
      const int RANK_WIDTH = 5;
      std::string rank = smart_format(std::to_string(rank_counter), RANK_WIDTH); // 順位

      const int NAME_WIDTH = 10;
      std::string name = smart_format(mp.first, NAME_WIDTH); // 名前

      const int SCORE_WIDTH = 7;
      std::string score = smart_format(std::to_string(mp.second), SCORE_WIDTH); // スコア

      std::string text = "| " + rank + " | " + name + " | " + score + " |";

      // String -> char[]
      char *record = new char[text.length()+1]; // Char配列の定義
      strcpy(record, text.c_str()); // String -> Char

      mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, record); // 描画

      loop_counter++;
      rank_counter++;
    }

    // 枠
    mvaddstr(RANKING_START_Y+loop_counter, RANKING_START_X, "--------------------------------");

    usleep(10000);
    refresh();
  }

  endwin();
}
