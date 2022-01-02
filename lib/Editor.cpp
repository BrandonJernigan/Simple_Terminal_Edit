//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

Editor::Editor()
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    window = newpad(max_y, max_x);
    filename = "untitled";
}

Editor::Editor(string filepath)
{
    ifstream file(filepath);
    if (file.is_open())
    {
        while(!file.eof())
        {
            string line;
            getline(file, line);
            text.push_back(line);
        }
    }

    window = newpad(text.size(), getmaxx(stdscr));
    filename = filepath;
}

void Editor::update()
{
    prefresh(window, 0, 0, 0, 0, getmaxy(stdscr) - 1, getmaxx(stdscr));
}

Mode Editor::get_mode()
{
    return mode;
}

void Editor::print_content()
{
    for(int i = 0; i < text.size(); i++)
    {
        mvwprintw(window, i, 0, text.at(i).c_str());
        prefresh(window, 0, 0, 0, 0, getmaxy(stdscr), getmaxx(stdscr));
    }
}

void Editor::handle_input(int input)
{
    switch(input)
    {
        case 81:
            mode = quit;
    }
}