#include <ncurses.h>
#include "Editor.h"

using namespace std;

int main(int argc, char* argv[]) {
    initscr();
    noecho();
    cbreak();

    Editor editor = argc > 1
            ? Editor(stdscr, argv[1])
            : Editor(stdscr);

    editor.print_content();

    bool running = true;
    while(running)
    {
        int input = getch();
        if (input == 81)
        {
            running = false;
        }
    }
    endwin();
    return 0;
}
