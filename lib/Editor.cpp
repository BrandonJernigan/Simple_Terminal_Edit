//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

Editor::Editor()
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    x = y = 0;
    mode = normal;
    filename = "untitled";
    window = newpad(max_y, max_x);
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

    x = y = 0;
    mode = normal;
    filename = filepath;
    window = newpad(text.size(), getmaxx(stdscr));
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
        case KEY_UP:
            move_up();
            break;

        case KEY_DOWN:
            this->move_down();
            break;

        case KEY_LEFT:
            move_left();
            break;

        case KEY_RIGHT:
            move_right();
            break;

        default:
            if(mode == normal)
            {
                normal_input(input);
            }
            else
            {
                insert_input(input);
            }
            break;
    }
    update();
}

void Editor::move_up()
{
    if(y > 0)
    {
        y--;
        wmove(window, y, x);
    }
}

void Editor::move_down()
{
    if(y < (getmaxy(stdscr) - 1))
    {
        y++;
        wmove(window, y, x);
    }
}

void Editor::move_left()
{
    if(x > 0)
    {
        x--;
        wmove(window, y, x);
    }
}

void Editor::move_right()
{
    if(x < getmaxx(stdscr))
    {
        x++;
        wmove(window, y, x);
    }
}

void Editor::normal_input(int input)
{
    if(input == 81)
    {
        mode = quit;
    }
    else if(input == 73)
    {
        mode = insert;
    }
}

void Editor::insert_input(int input)
{
    if(input == 27)
    {
        mode = normal;
    }
}