//
// Created by Brandon Jernigan on 1/2/22.
//

#ifndef SIMPLE_TERMINAL_EDIT_FILE_HANDLER_H
#define SIMPLE_TERMINAL_EDIT_FILE_HANDLER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class File_Handler
{
public:
    string filename;
    vector<string> text;

    explicit File_Handler(string filepath);
    void open_file();
    void save_file();

    __wrap_iter<string *> get_substring(int length);
    string get_substring(int row, int position, int length);
    void insert_character(int row, int col, int input);
    void insert_line(__wrap_iter<const string *> position, string input);
    void delete_line(__wrap_iter<const string *> length);
    void delete_characters(int row, int position, int length);
};

#endif //SIMPLE_TERMINAL_EDIT_FILE_HANDLER_H
