#include <iostream>
#include <ncurses.h>

int main() {
    initscr();
    noecho();
    cbreak();

    printw("Working..?");

    getch();
    endwin();
    return 0;
}
