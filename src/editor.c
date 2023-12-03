//
// Created by xdanep on 3/12/23.
//
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "files.h"
#include "terminal.h"
#include "editor.h"
/*** Output ***/
void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // Reposition cursor

    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);  // Reposition cursor
}

void editorDrawRows() {
    int y;
    for (y = 0; y < E.screenrows; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

/*** Input ***/
char editorReadKey() {
    int nread;
    char c;

    // Read character from terminal
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

void editorProcessKeypress() {
    char c = editorReadKey();

    // Check if character is a control character
    switch (c) {
        case CTRL_KEY('q'): // Quit
            write(STDOUT_FILENO, "\x1b[2J", 4);  // Clear screen
            write(STDOUT_FILENO, "\x1b[H", 3);   // Reposition cursor
            fclose(fileIn);                         // Close file
            exit(EXIT_SUCCESS);
            break;
    }
}

void initEditor() {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}