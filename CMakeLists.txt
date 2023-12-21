cmake_minimum_required(VERSION 3.26)
project(texed C)

add_link_options(-lncurses)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(texed
        src/main.c
        src/file.c
        src/includes/file.h
        src/editor.c
        src/includes/editor.h
        src/screen.c
        src/includes/screen.h
        src/cli.c
        src/includes/cli.h
        src/text.c
        src/includes/text.h
        src/log.c
        src/includes/log.h)
