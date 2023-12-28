//
// Created by xdanep on 3/12/23.
//
#include <ncurses.h>
#include <termios.h>


#ifndef TEXED_SCREEN_H
#define TEXED_SCREEN_H

// Variables
extern struct termios original_state;
extern char *title;

// Function prototypes
void startScreen();
void screenInfo();
void restore_terminal_state();
#endif // TEXED_SCREEN_H
