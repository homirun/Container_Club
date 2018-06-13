from curses import wrapper
import curses
from time import sleep

def main(stdscr):
    # clearコマンド
    stdscr.clear()

    for i in range(30):
        stdscr.addstr(str(i))
        stdscr.addstr(i, i, "hoge",curses.A_REVERSE)  # y, x, str, options
        stdscr.refresh()
        # スリープ挟まんと死ぬ
        sleep(0.1)
        stdscr.clear()

    stdscr.refresh()

    # 多分キー取ってる
    stdscr.getkey()

if __name__ == '__main__':
    wrapper(main)