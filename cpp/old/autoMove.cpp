#include<iostream>
#include<ncurses.h>

using namespace std;

int px = 0;
int py = 0;
int level = 800;
int isHead = 1;

int ch = 'l';

/* prototype */
void run(void);
/************/

int main(void){
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  bkgd(COLOR_PAIR(1));
  while(1){
    run();
    refresh();
  }
  endwin();
  return 0;
}

void move(double x, double y){
  mvaddch(py, px, ' ');

  px = x;
  py = y;

  mvaddch(py, px, 'D');
}

void run(void){
  clear();
  timeout(0);
  ch = getch();
  switch(ch){
    case 'h':
      isHead = 3;
      break;
    case 'j':
      isHead = 2;
      break;
    case 'k':
      isHead = 0;
      break;
    case 'l':
      isHead = 1;
      break;
  }

  switch(isHead){
  case 0:
    move(px, py--);
    break;
  case 1:
    move(px++, py);
    break;
  case 2:
    move(px, py++);
    break;
  case 3:
    move(px--, py);
    break;
  }

  //mvprintw(py--, px, "*");
  napms(level);


}