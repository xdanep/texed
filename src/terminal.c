//
// Created by xdanep on 2/12/23.
//

#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode() {
    // Set terminal attributes
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    struct termios raw = orig_termios;

    // Get terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    // Disable echo
    raw.c_lflag &= ~(ECHO | ICANON);

    // Set terminal attributes
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}