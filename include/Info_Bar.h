//
// Created by Brandon Jernigan on 1/4/22.
//

#ifndef SIMPLE_TERMINAL_EDIT_INFO_BAR_H
#define SIMPLE_TERMINAL_EDIT_INFO_BAR_H

#include "Editor.h"

inline void print_info_bar(WINDOW* window, string filename, long line_count, string mode)
{
    wmove(window, 0, 0);                                            // Move the cursor to the top of the window
    wattron(window, A_REVERSE);                                     // Reverse background and foreground to make bar stand out

    string document_info = "document: " + filename;                 // Format the document name
    string line_info = "lines: " + to_string(line_count);           // Format the line count
    string mode_info = "mode: " + mode;                             // Format the current mode

    wprintw(window, document_info.c_str());                         // Print the editor information
    wprintw(window, " | ");                                         // Separate information with a pipe character
    wprintw(window, line_info.c_str());
    wprintw(window, " | ");
    wprintw(window, mode_info.c_str());

    wattroff(window, A_REVERSE);                                    // Undo background and foreground reverse
    wrefresh(window);                                               // Call a refresh to the window
}

#endif //SIMPLE_TERMINAL_EDIT_INFO_BAR_H
