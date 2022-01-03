//
// Created by Brandon Jernigan on 1/2/22.
//

#include "File_Handler.h"

#include <utility>

File_Handler::File_Handler(string filepath)
{
    filename = std::move(filepath);
}

void File_Handler::open_file()
{
    ifstream file(filename);
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

void File_Handler::save_file()
{
    ofstream file (filename.c_str());
    if(file.is_open()) {
        for (auto & line : text)
        {
            file << line << endl;
        }
    }
    file.close();
}

__wrap_iter<string *> File_Handler::get_substring(int length)
{
    return text.begin() + length;
}

string File_Handler::get_substring(int row, int position, int length)
{
    return text.at(row).substr(position, length);
}

void File_Handler::insert_character(int row, int col, int input)
{
    text.at(row).insert(col, 1, (char)input);
}

void File_Handler::insert_line(__wrap_iter<const string *> position, string input)
{
    text.insert(position, input);
}

void File_Handler::delete_line(__wrap_iter<const string *> length)
{
    text.erase(length);
}

void File_Handler::delete_characters(int row, int position, int length)
{
    text.at(row).erase(position, length);
}