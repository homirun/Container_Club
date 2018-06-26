#include<iostream>
#include<ncurses.h>

using namespace std;

int px = 0;
int py = 0;
int ch;
int level = 800;


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

void run(void){
  clear();
  mvprintw(py++, px++,"$");
  //ch = getch();
  napms(level);

  // switch(ch){
  //   case 'h':
  //     mvprintw(py, px--, "*");
  //     break;
  //   case 'j':
  //     mvprintw(py++, px, "*");
  //     break;
  //   case 'k':
  //     mvprintw(py--, px, "*");
  //     break;
  //   case 'l':
  //     mvprintw(py, px++, "*");
  //     break;
  // }
}