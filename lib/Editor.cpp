//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

Editor::Editor(WINDOW* window)
{
    this->window = window;
}

Editor::Editor(WINDOW* window, const string& file_path)
{
    this->window = window;

    ifstream file(file_path);
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

void Editor::print_content()
{
    for(int i = 0; i < text.size(); i++)
    {
        mvwprintw(window, i, 0, text.at(i).c_str());
    }
}