//
// Created by Brandon Jernigan on 1/1/22.
//

#include "Editor.h"

Editor::Editor()
{
    setup_editor("untitled");

    /* Initialize text vector with data */
    file_handler->text.emplace_back("");
    file_handler->text.emplace_back("");

    /* Create a pad window to allow for height beyond the standard screen height */
    window = newpad(getmaxy(stdscr), getmaxx(stdscr));
}

Editor::Editor(string filepath)
{
    setup_editor(filepath);

    /* Set up file handler with filepath provided */
    file_handler->open_file();

    /* Create a pad window to allow for height beyond the standard screen height */
    window = newpad(file_handler->text.size(), getmaxx(stdscr));
}

Editor::~Editor()
{
    delwin(window);
}

void Editor::setup_editor(string filepath)
{
    mode = normal;

    x = y = 0;
    top = 0;
    bottom = getmaxy(stdscr) - 2;

    file_handler = new File_Handler(filepath);
}

void Editor::update()
{
    /* Call to p-refresh since the window is a pad */
    prefresh(window, top, 0, 1, 0, getmaxy(stdscr) - 1, getmaxx(stdscr));
}

string Editor::get_filename()
{
    return file_handler->filename;
}

Mode Editor::get_mode()
{
    return mode;
}

string Editor::get_mode_info()
{
    return mode == insert ? "insert" : "normal";
}

long Editor::get_lines()
{
    return (long)file_handler->text.size();
}

void Editor::print_content()
{
    wclear(window);
    for(int i = 0; i < file_handler->text.size(); i++)
    {
        wmove(window, i, 0);
        wprintw(window, file_handler->text.at(i).c_str());
        prefresh(window, 0, 0, 1, 0, getmaxy(stdscr), getmaxx(stdscr));
    }

    /* Move the cursor back to x and y of previous state */
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

    /* Move x position to the end of each line */
    if(x > file_handler->text.at(y).length())
    {
        x = file_handler->text.at(y).length();
    }
    wmove(window, y, x);
}

void Editor::move_down()
{
    /* Ensure the next line is available */
    if(y + 1 < file_handler->text.size() - 1)
    {
        /* Window scroll */
        if(y >= bottom)
        {
            top++;
            bottom++;
        }
        y++;

        /* Move x position to the end of each line */
        if(x > file_handler->text.at(y).length())
        {
            x = file_handler->text.at(y).length();
        }
        wmove(window, y, x);
    }
}

void Editor::move_left()
{
    /* Move up a line if at left most point,
     * with an available line above */
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
        /* Make sure line below is available, and if so
        * move down one line */
        if(x == file_handler->text.at(y).length()
        && y + 1 < file_handler->text.size() - 1)
        {
            /* Window scroll */
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
        /* Shift-Q */
        case 81:
            mode = quit;
            break;

        /* Shift-I */
        case 73:
            mode = insert;
            break;

        /* Shift-S */
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
        /* Escape key */
        case 27:
            mode = normal;
            break;

        /* Enter key */
        case 10:
        case KEY_ENTER:
            handle_enter_key();
            break;

        /* Backspace key */
        case 127:
        case KEY_BACKSPACE:
            handle_backspace_key();
            break;

        /* Delete key */
        case KEY_DC:
            handle_delete_key();
            break;

        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_CATAB:
        case KEY_STAB:
        case 9:
            handle_tab_key();
            break;

        default:
            handle_default_key((char)input);
            break;
    }
}

void Editor::handle_enter_key()
{
    /* Resize the window if at the last line */
    if(y + 1 >= file_handler->text.size() - 1)
    {
        wresize(window, file_handler->text.size() + 1, getmaxx(stdscr));
    }

    /* Split current line at x if not at the end of the line */
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
    /* Go up one line if at the left most point */
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
    /* Bring line up if at end of line */
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

void Editor::handle_tab_key()
{
    file_handler->text.at(y).insert(x, 4, ' ');
    x += 4;
    wmove(window, y, x);
}

void Editor::handle_default_key(char input)
{
    file_handler->insert_character(y, x, input);
    x++;
    wmove(window, y, x);
}