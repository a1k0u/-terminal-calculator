cmake_minimum_required(VERSION 3.21)
project(terminal_calculator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(terminal_calculator
        main.c
        libs/node.h
        libs/string.c
        libs/string.h)
