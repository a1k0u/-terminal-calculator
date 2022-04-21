cmake_minimum_required(VERSION 3.21)
project(terminal_calculator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_executable(terminal_calculator
        main.c
        libs/str.c
        libs/str.h
        libs/stack.c
        libs/stack.h
        libs/node.c
        libs/node.h
        libs/parsing.c
        libs/parsing.h
        )

target_link_libraries(terminal_calculator m)
