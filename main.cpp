#include <ncurses.h>
#include "Editor.h"

using namespace std;

int main(int argc, char* argv[]) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    Editor editor = argc > 1
            ? Editor(argv[1])
            : Editor();

    wrefresh(stdscr);
    refresh();

    while(editor.get_mode() != quit)
    {
        editor.print_content();
        editor.update();

        int input = getch();
        editor.handle_input(input);
    }

    endwin();
    return 0;
}
