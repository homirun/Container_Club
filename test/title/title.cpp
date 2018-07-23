#include <iostream>
#include <ncurses.h>
#include <string>
#include "unistd.h" // sleepで使う

using namespace std;

int terx, tery;

// 空白を埋める(引数の数だけスペースを返す)
string smart_format(string str, int column_width){

  int str_len = str.length();
  int need_spaces = column_width - str_len;

  if(need_spaces < 0){
    return "\0";
  }

  string tmp;
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
  // cbreak(); // 1文字打ったら終わり!!
  timeout(100); // nodelay()とほぼ同義. ERRを返すまでのタイムアウト時間.
  curs_set(0); // カーソルの見え方 : 透過

  // refresh();

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

    // ノンブロッキング ON
    timeout(-1);
    curs_set(1); // カーソルの見え方 : 透過
    echo();

    // 入力の受付
    const int TEXT_LENGTH = 40;
    char txt[TEXT_LENGTH];
    move(RANKING_START_Y+loop_counter, RANKING_START_X+13);
    getnstr(txt, TEXT_LENGTH);

    // 出力 for Debug
    mvaddstr(0, 0, txt);

    // ノンブロッキング OFF
    timeout(100);
    usleep(10000);
    refresh();

  }

  endwin();
}
