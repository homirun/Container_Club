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
    erase();
    run();
    refresh();
  }
  endwin();
  return 0;
}

void run(void){
  //timeout(0);
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
    mvprintw(py--, px, "*");
    break;
  case 1:
    mvprintw(py, px++, "*");
    break;
  case 2:
    mvprintw(py++, px, "*");
    break;
  case 3:
    mvprintw(py, px--, "*");
    break;
  }

  //mvprintw(py--, px, "*");
  napms(level);

}