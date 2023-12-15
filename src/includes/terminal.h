//
// Created by xdanep on 2/12/23.
//
#include <termios.h>

#ifndef TEXED_TERMINAL_H
#define TEXED_TERMINAL_H
#define CTRL_KEY(k) ((k) & 0x1f) // Bitwise AND operator

// Variables
struct editorConfig {
    int cx, cy;
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

extern struct editorConfig E;

// Function prototypes
void disableRawMode();
void enableRawMode();
void die(const char *s);
int getWindowSize(int *rows, int *cols);
#endif //TEXED_TERMINAL_H
