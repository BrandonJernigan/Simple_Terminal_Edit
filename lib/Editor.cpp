//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

Editor::Editor(WINDOW* window)
{
    this->window = window;
    filename = "untitled";
}

Editor::Editor(WINDOW* window, const string& filepath)
{
    this->window = window;
    filename = filepath;

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