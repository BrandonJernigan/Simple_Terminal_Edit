cmake_minimum_required(VERSION 3.21)
project(Simple_Terminal_Edit)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

include_directories(Simple_Terminal_Edit ${CMAKE_SOURCE_DIR}/include ${CURSES_INCLUDE_DIR})
add_executable(Simple_Terminal_Edit main.cpp include/Editor.h lib/Editor.cpp)
target_link_libraries(Simple_Terminal_Edit ${CURSES_LIBRARIES})
