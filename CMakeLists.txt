cmake_minimum_required(VERSION 3.26)
project(texed C)

set(CMAKE_C_STANDARD 11)

add_executable(texed
        src/main.c
        src/files.c
        src/files.h
        src/terminal.c
        src/terminal.h)
