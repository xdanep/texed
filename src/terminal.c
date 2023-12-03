//
// Created by xdanep on 2/12/23.
//

#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

struct editorConfig E;

void disableRawMode() {
    // Set terminal attributes
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    // Get terminal attributes
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);

    struct termios raw = E.orig_termios;

    // Set terminal attributes
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // Input flags
    raw.c_oflag &= ~(OPOST);                                  // Output flags
    raw.c_cflag |= (CS8);                                     // Control flags
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);          // Local flags
    raw.c_cc[VMIN] = 0;                              // Minimum number of bytes of input needed before read() can return
    raw.c_cc[VTIME] = 1;                             // Maximum amount of time to wait before read() returns

    // Set terminal attributes
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

// Print error message and exit
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // Reposition cursor

    // Print error message
    perror(s);
    exit(EXIT_FAILURE);
}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    // Get window size
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}