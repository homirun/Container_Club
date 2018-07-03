#include <random>
#include <ncurses.h>
using namespace std;


void mvcursor(char num_move, WINDOW *win);
void addapple();

int terx, tery;

class MyCursor
{
  public:
    double myX;
    double myY;
    char myobject = '@';

  MyCursor(double x, double y) : myX(x), myY(y)
  {
    
  }

  void move(double x, double y)
  {
    mvaddch(myY, myX, ' ');

    myX = x;
    myY = y;

    mvaddch(myY, myX, myobject);
  }


  void mycursor(char num_move)
  {
    if (num_move == 'h')
      this -> move(myX - 1, myY);
    else if (num_move == 'j')
      this -> move(myX, myY + 1);
    else if (num_move == 'k')
      this -> move(myX, myY - 1);
    else if (num_move == 'l')
      this -> move(myX + 1, myY);
  }


  bool isTouching(MyCursor &obj)
  {
    return (myX == obj.myX && myY == obj.myY);
  }
    
};

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
      random_device rnd;
      mt19937 mt(rnd());
      uniform_int_distribution<> randX(0, terx - 1);
      uniform_int_distribution<> randY(0, tery - 1);

      this -> move(randX(mt), randY(mt));
    }

};


int main()
{
  WINDOW *w = initscr();

  getmaxyx(w, tery, terx);

  noecho();
  cbreak();

  curs_set(0);

  MyCursor obj(0, 0);
  AppleCursor ap;

  move(0, 0);

  ap.pop_apple();
  
  while (true)
  {
    // mvcursor(m, w);
    obj.mycursor(getch());

    if (obj.isTouching(ap))
    {
      ap.pop_apple();
      obj.move(obj.myX, obj.myY);
    }

    refresh();
  }

  endwin();
}


// random
// random_device rnd;
// mt19937 mt(rnd());
// uniform_int_distribution<> rand100(0, 99);
// cout << rand100(mt) << endl;





// void mvcursor(char num_move, WINDOW *win)
// {
//   int x, y;
//   getyx(win, y, x);
// 
//   if (num_move == 'h' && x != 0)
//   {
//     addch(' ');
//     mvaddch(y, x - 1, '@');
//     move(y, x - 1);
//   }
//   else if (num_move == 'j')
//   {
//     addch(' ');
//     mvaddch(y + 1, x, '@');
//     move(y + 1, x);
//   }
//   else if (num_move == 'k' && y != 0)
//   {
//     addch(' ');
//     mvaddch(y - 1, x, '@');
//     move(y - 1, x);
//   }
//   else if (num_move == 'l')
//   {
//     addch(' ');
//     addch('@');
//     move(y, x + 1);
//   }
// }

// void addapple()
// {
//   int ax, ay;
// 
//   ax = 100;
//   ay = 100;
// 
//   mvaddch(ay, ax, 'A');
// }
