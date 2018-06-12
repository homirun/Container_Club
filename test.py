from curses import wrapper
import curses
from time import sleep
def main(stdscr):
    stdscr.clear()
    for i in range(30):
        stdscr.addstr(str(i))
        stdscr.addstr(i, i, "hoge",curses.A_REVERSE)
        stdscr.refresh()
        sleep(0.1)
        stdscr.clear()

    stdscr.refresh()
    stdscr.getkey()

if __name__ == '__main__':
    wrapper(main)