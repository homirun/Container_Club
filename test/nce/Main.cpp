#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;

int main()
{
  winsize ws;

  ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws);

  // cout << ws.ws_col << endl;
  // cout << ws.ws_row << endl;

  // cout << "[0;0H";

  for (int i = 0; i < ws.ws_row - 1; i++)
  {
    for (int j = 0; j < ws.ws_col; j++)
    {
      if (i == 0 && j == 0)
        // cout << "╭";

      else if (i == 0 && j == ws.ws_col - 1)
        // cout << "╮";

      else if (i == ws.ws_row - 2 && j == 0)
        // cout << "╰";

      else if (i == ws.ws_row - 2 && j == ws.ws_col - 1)
        // cout << "╯";


      else if (i == 0 || i == ws.ws_row - 2)
        // cout << "─";

      else if (j == 0 || j == ws.ws_col - 1)
        // cout << "│";

      else
        // cout << " ";

      if (j == ws.ws_col)
        // cout << endl;
    }
  }

}
