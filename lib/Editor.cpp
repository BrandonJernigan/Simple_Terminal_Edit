//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

#include <utility>

Editor::Editor()
{
    setup_editor("untitled");
    file_handler->text.emplace_back("");
    file_handler->text.emplace_back("");
    window = newpad(getmaxy(stdscr), getmaxx(stdscr));
}

Editor::Editor(string filepath)
{
    setup_editor(filepath);
    file_handler->open_file();
    window = newpad(file_handler->text.size(), getmaxx(stdscr));
}

void Editor::setup_editor(string filepath)
{
    mode = normal;

    x = y = 0;
    top = 0;
    bottom = getmaxy(stdscr) - 1;

    file_handler = new File_Handler(filepath);
}

void Editor::update()
{
    prefresh(window, top, 0, 0, 0, getmaxy(stdscr) - 1, getmaxx(stdscr));
}

Mode Editor::get_mode()
{
    return mode;
}

void Editor::print_content()
{
    wclear(window);
    for(int i = 0; i < file_handler->text.size(); i++)
    {
        wmove(window, i, 0);
        wprintw(window, file_handler->text.at(i).c_str());
        prefresh(window, 0, 0, 0, 0, getmaxy(stdscr), getmaxx(stdscr));
    }
    wmove(window, y, x);
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
        if(y <= top)
        {
            top--;
            bottom--;
        }
        y--;
    }

    if(x > file_handler->text.at(y).length())
    {
        x = file_handler->text.at(y).length();
    }
    wmove(window, y, x);
}

void Editor::move_down()
{
    if(y + 1 < file_handler->text.size() - 1)
    {
        if(y >= bottom)
        {
            top++;
            bottom++;
        }
        y++;

        if(x > file_handler->text.at(y).length())
        {
            x = file_handler->text.at(y).length();
        }
        wmove(window, y, x);
    }
}

void Editor::move_left()
{
    if(x == 0 && y > 0)
    {
        x = file_handler->text.at(y - 1).length();
        y--;
    }
    else if(x > 0)
    {
        x--;
    }
    wmove(window, y, x);
}

void Editor::move_right()
{
    if(y < file_handler->text.size() - 1)
    {
        if(x == file_handler->text.at(y).length()
        && y + 1 < file_handler->text.size() - 1)
        {
            if(y >= bottom)
            {
                top++;
                bottom++;
            }

            y++;
            x = 0;
            wmove(window, y, x);
        }
        else
        {
            x++;
            wmove(window, y, x);
        }
    }
}

void Editor::normal_input(int input)
{
    switch(input) {
        case 81:
            mode = quit;
            break;

        case 73:
            mode = insert;
            break;

        case 83:
            file_handler->save_file();
            break;

        default:
            break;
    }
}

void Editor::insert_input(int input)
{
    switch(input)
    {
        case 27:
            mode = normal;
            break;

        case 10:
        case KEY_ENTER:
            handle_enter_key();
            break;

        case 127:
        case KEY_BACKSPACE:
            handle_backspace_key();
            break;

        case KEY_DC:
            handle_delete_key();
            break;

        default:
            handle_default_key((char)input);
            break;
    }
}

void Editor::handle_enter_key()
{
    if(y + 1 >= file_handler->text.size() - 1)
    {
        wresize(window, file_handler->text.size() + 1, getmaxx(stdscr));
    }

    auto index = file_handler->get_substring(y + 1);
    if(x < file_handler->text.at(y).length())
    {
        int substr_length = file_handler->text.at(y).length() - x;
        auto substr = file_handler->get_substring(y, x, substr_length);
        file_handler->insert_line(index, substr);
        file_handler->delete_characters(y, x, substr_length);
    }
    else
    {
        file_handler->insert_line(index, "");
    }

    x = 0;
    move_down();
}

void Editor::handle_backspace_key()
{
    if(x == 0 && y > 0)
    {
        x = file_handler->text.at(y - 1).length();
        file_handler->text.at(y - 1) += file_handler->text.at(y);

        auto substr_length = file_handler->get_substring(y);
        file_handler->delete_line(substr_length);
        move_up();
    }
    else if(x > 0)
    {
        file_handler->delete_characters(y, --x, 1);
        wmove(window, y, x);
    }
}

void Editor::handle_delete_key()
{
    if(x == file_handler->text.at(y).length()
       && y + 1 < file_handler->text.size() - 1)
    {
        file_handler->text.at(y) += file_handler->text.at(y + 1);
        auto substr_length = file_handler->get_substring(y + 1);
        file_handler->delete_line(substr_length);
    }
    else
    {
        file_handler->delete_characters(y, x, 1);
    }
}

void Editor::handle_default_key(char input)
{
    file_handler->insert_character(y, x, input);
    x++;
    wmove(window, y, x);
}