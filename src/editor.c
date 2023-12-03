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

enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

/*** Append buffer ***/
struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}
#define TEXED_VERSION "0.0.1"

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
        if(y==E.screenrows / 3) {
            char welcome[80];

            int welcomelen = snprintf(welcome, sizeof(welcome),
                                      "TexEd editor -- version %s", TEXED_VERSION);
            if(welcomelen > E.screencols) welcomelen = E.screencols;

            int padding = (E.screencols - welcomelen) / 2;
            if (padding) {
                abAppend(ab, "~", 1);
                padding--;
            }
            while (padding--) abAppend(ab, " ", 1);

            abAppend(ab, welcome, welcomelen);
        } else {
            abAppend(ab, "~", 1); // Print tilde
        }

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

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
    abAppend(&ab, buf, strlen(buf)); // Reposition cursor

    abAppend(&ab, "\x1b[?25h", 6); // Show cursor

    write(STDOUT_FILENO, ab.b, ab.len); // Write to terminal
    abFree(&ab); // Free buffer
}

/*** Init ***/
void initEditor() {
    E.cx = 0;
    E.cy = 0;

    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

/*** Input ***/
void editorMoveCursor(int key) {
    switch (key) {
        case ARROW_LEFT:
            if (E.cx != 0) {
                E.cx--;
            }
            break;
        case ARROW_RIGHT:
            if (E.cx != E.screencols - 1) {
                E.cx++;
            }
            break;
        case ARROW_UP:
            if (E.cy != 0) {
                E.cy--;
            }
            break;
        case ARROW_DOWN:
            if (E.cy != E.screenrows - 1) {
                E.cy++;
            }
            break;
    }
}

int editorReadKey() {
    int nread;
    char c;

    // Read character from terminal
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    if (c == '\x1b') {
        char seq[3];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }
        return '\x1b';
    } else {
        return c;
    }
}

void editorProcessKeypress() {
    int c = editorReadKey();

    // Check if character is a control character
    switch (c) {
        case CTRL_KEY('q'): // Quit
            write(STDOUT_FILENO, "\x1b[2J", 4);  // Clear screen
            write(STDOUT_FILENO, "\x1b[H", 3);   // Reposition cursor
            fclose(fileIn);                         // Close file
            exit(EXIT_SUCCESS);
            break;

        case HOME_KEY:
            E.cx = 0;
            break;
        case END_KEY:
            E.cx = E.screencols - 1;
            break;

        case PAGE_UP:
        case PAGE_DOWN:
            {
            int times = E.screenrows;
            while (times--)
                editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorMoveCursor(c);
            break;
    }
}