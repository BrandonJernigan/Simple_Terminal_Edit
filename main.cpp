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

    while(editor.get_mode() != quit)
    {
        int input = getch();
        editor.print_content();
        editor.handle_input(input);
    }

    endwin();
    return 0;
}
