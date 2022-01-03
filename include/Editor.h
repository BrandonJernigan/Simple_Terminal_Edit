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
    Mode mode;
    WINDOW* window;
    int top, bottom;
    File_Handler* file_handler;

    void setup_editor(string filename);

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    void normal_input(int input);
    void insert_input(int input);
    void handle_enter_key();
    void handle_backspace_key();
    void handle_delete_key();
    void handle_default_key(char input);

public:
    explicit Editor();
    Editor(string filepath);

    void update();
    Mode get_mode();
    void print_content();
    void handle_input(int input);
};

#endif //SIMPLE_TERMINAL_EDIT_EDITOR_H
