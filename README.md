<h1 align="center">Simple Terminal Edit</h1>
<h6 align="center">Written in C++ using ncurses</h6>

<p align="center">
  <img width="300" alt="logo" src="https://user-images.githubusercontent.com/81219815/147907184-458bcbff-6510-4540-a410-235a01d896e2.png">
</p>


## Usage
This application is a simple exploration of creating a terminal based text editor. It aims to have a similarity to VIm and/or Nano. 
It is simple, with the intention of being an easy to expand project.


#### * Still under development *
- Currently working to add support for the tab key. (Backspace, Enter, and Delete do work currently)
- Future addition of top info bar.
- Future addition of custom syntax highlighter for C++.


#### Application Specifications
- C++ version 17
- ncurses version 6.3
- CMake version 3.21
- Apple clang version 13.0.0
- macOS Monterey version 12.1

#### Key Mappings
```c++
/* Normal Mode */
Save File   : Shift-S
Quit        : Shift-Q
Insert Mode : Shift-I

/* Insert Mode */
Move Up     : Up Arrow
Move Down   : Down Arrow
Move Left   : Left Arrow
Move Right  : Right Arrow
Normal Mode : Escape
```

#### Setup

###### Clone the repository
```
git clone https://github.com/BrandonJernigan/Simple_Terminal_Edit.git
```
###### Ensure that you have ncurses
```c++
// Ensure that you have ncurses installed
```
###### Run with command line argument of file path
```c++
// After compiling and linking, run the application with 
// the path to the file you want to edit. Otherwise, 
// it will default to a file named undefined.

/* Example */
./Simple_Terminal_Edit ~/Documents/myfile.txt
```
