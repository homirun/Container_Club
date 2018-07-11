#include<iostream>
#include <string>
#include<ncurses.h>

using namespace std;

// 先頭の角度
string heading = "top";

// 体のパーツ
struct Body {
  int x;
  int y;
  bool is_head;
};

void run(){

  // 100体のパーツ
  struct Body body[100];

  // プロパティの代入
  body[0].x = 100;
  body[0].y = 200;
  body[0].is_head = true;

  // 出力
  cout << "body[0][x]=" << body[0].x << "\n";
  cout << "body[0][y]=" << body[0].y << "\n";
  cout << "body[0][is_head]=" << body[0].is_head << "\n";

}

int main(void){

  run();

  return 0;

}