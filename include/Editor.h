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

class Editor
{
private:
    WINDOW* window;
    string file_name;
    vector<string> text;

public:
    explicit Editor(WINDOW* window);
    Editor(WINDOW* window, const string& file_path);

    void print_content();
};

#endif //SIMPLE_TERMINAL_EDIT_EDITOR_H
