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

using namespace std;

Title::Title()
{

}


// タイトル画面
void Title::popTitle(char *user_name, int TEXT_LENGTH)
{
  const int RANKING_START_Y = Setting::terY / 2 - 5;
  const int RANKING_START_X = Setting::terX / 2 - 40;
  int loop_counter = 0;

  while (1)
  {
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

    clear();
    refresh();
    break;
  }
}
