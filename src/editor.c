//
// Created by xdanep on 3/12/23.
//
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "files.h"
#include "terminal.h"
#include "editor.h"
/*** Append buffer ***/
struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b, ab->len + len);
    if (new == NULL) return;
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}

void abFree(struct abuf *ab) {
    free(ab->b);
}

/*** Output ***/
void editorDrawRows(struct abuf *ab) {
    int y;
    for (y = 0; y < E.screenrows; y++) {
        abAppend(ab, "~", 1); // Print tilde

        abAppend(ab, "\x1b[K", 3); // Clear line

        if (y < E.screenrows - 1) {
            abAppend(ab, "\r\n", 2); // Print newline
        }
    }
}

void editorRefreshScreen() {
    struct abuf ab = ABUF_INIT; // Initialize buffer

    abAppend(&ab, "\x1b[?25l", 6); // Hide cursor
    abAppend(&ab, "\x1b[H", 3);  // Reposition cursor

    editorDrawRows(&ab); // Draw rows

    abAppend(&ab, "\x1b[H", 3); // Reposition cursor
    abAppend(&ab, "\x1b[?25h", 6); // Show cursor

    write(STDOUT_FILENO, ab.b, ab.len); // Write to terminal
    abFree(&ab); // Free buffer
}

/*** Init ***/
void initEditor() {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
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