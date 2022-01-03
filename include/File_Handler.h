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
    string filename;                                                        // Path to the file
    vector<string> text;                                                    // Vector of text file text

    explicit File_Handler(string filepath);

    void open_file();                                                       // Get the contents of the file, stored in text
    void save_file();                                                       // Overwrite all contents of file with data in text

    __wrap_iter<string *> get_substring(int length);                        // Return substrings
    string get_substring(int row, int position, int length);

    void insert_character(int row, int col, int input);                     // Insert operations
    void insert_line(__wrap_iter<const string *> position, string input);

    void delete_line(__wrap_iter<const string *> length);                   // Deletion operations
    void delete_characters(int row, int position, int length);
};

#endif //SIMPLE_TERMINAL_EDIT_FILE_HANDLER_H
