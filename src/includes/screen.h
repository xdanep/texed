//
// Created by xdanep on 3/12/23.
//
#include <ncurses.h>

#ifndef TEXED_SCREEN_H
#define TEXED_SCREEN_H

// Variables
extern WINDOW *texed; // Window
extern char *title;

// Function prototypes
void startScreen();
void screenInfo();
#endif // TEXED_SCREEN_H
