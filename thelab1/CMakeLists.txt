cmake_minimum_required(VERSION 3.26)
project(thelab1_2 C)

set(CMAKE_C_STANDARD 23)

add_executable(thelab1_2 main.c)
target_link_libraries(thelab1_2 ncurses)


