#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    initscr();
    noecho();
    cbreak();

    printw("Working..?");

    vector<string> text;
    if(argc > 1)
    {
        ifstream file(argv[1]);
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

    if(!text.empty())
    {
        for(int i = 0; i < text.size(); i++)
        {
            mvprintw(i, 0, text.at(i).c_str());
        }
    }

    bool running = true;
    while(running)
    {
        int input = getch();
        if (input == 81)
        {
            running = false;
        }
    }
    endwin();
    return 0;
}
