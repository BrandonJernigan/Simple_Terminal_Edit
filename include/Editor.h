//
// Created by Brandon Jernigan on 1/1/22.
//

#ifndef SIMPLE_TERMINAL_EDIT_EDITOR_H
#define SIMPLE_TERMINAL_EDIT_EDITOR_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum Mode {normal, insert, quit};

class Editor
{
private:
    Mode mode;
    WINDOW* window;
    string filename;
    vector<string> text;

public:
    explicit Editor(WINDOW* window);
    Editor(WINDOW* window, const string& filepath);

    Mode get_mode();
    void print_content();
    void handle_input(int input);
};

#endif //SIMPLE_TERMINAL_EDIT_EDITOR_H
