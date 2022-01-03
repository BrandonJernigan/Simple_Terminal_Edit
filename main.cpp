#include <ncurses.h>
#include "Editor.h"

using namespace std;

int main(int argc, char* argv[]) {
    initscr();                              // Initialize ncurses standard screen
    noecho();                               // Disable echo of keyboard input
    cbreak();                               // Allow for signal interrupt
    keypad(stdscr, TRUE);                   // Allow for use of arrow keys

    Editor editor = argc > 1                // Create a new editor class (blank or with file)
            ? Editor(argv[1])
            : Editor();

    wrefresh(stdscr);
    refresh();                             // Call to refresh everything after initial setup

    while(editor.get_mode() != quit)       // Main program loop, dependent on the one and only editor class
    {
        editor.print_content();           // Display text
        editor.update();                  // Refresh editor window

        int input = getch();              // Wait for input & handle it
        editor.handle_input(input);
    }

    endwin();                            // Clean up ncurses standard screen
    return 0;
}
