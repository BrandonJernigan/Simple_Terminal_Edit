//
// Created by Brandon Jernigan on 1/1/22.
//

#ifndef SIMPLE_TERMINAL_EDIT_EDITOR_H
#define SIMPLE_TERMINAL_EDIT_EDITOR_H

#include <ncurses.h>
#include "File_Handler.h"

using namespace std;

enum Mode {normal, insert, quit};

class Editor
{
private:
    int x, y;
    Mode mode;                                  // Reference for types of input that can be performed
    WINDOW* window;                             // The editor window, ncurses pad
    int top, bottom;                            // Values to perform sliding window technique for scroll
    File_Handler* file_handler;                 // Class to handle text and file specific tasks

    void setup_editor(string filename);         // Base editor settings

    void move_up();                             // Window specific movement
    void move_down();
    void move_left();
    void move_right();

    void normal_input(int input);               // Normal mode input cases
    void insert_input(int input);               // Insert mode input cases

    void handle_enter_key();                    // Handlers for specific keys
    void handle_backspace_key();
    void handle_delete_key();
    void handle_tab_key();
    void handle_default_key(char input);        // Handler for general key press, not already covered

public:
    explicit Editor();
    Editor(string filepath);
    ~Editor();

    void update();
    Mode get_mode();                            // Return the current mode of editor
    void print_content();                       // Display text
    void handle_input(int input);               // Public call to handle keypress
};

#endif //SIMPLE_TERMINAL_EDIT_EDITOR_H
