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
        case CTRL_KEY('q'):
            fclose(fileIn);
            exit(EXIT_SUCCESS);
            break;
    }
}