//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "files.h"
#include "terminal.h"
#include "editor.h"

int main(int argc, char *argv[]) {
    // Variables
    char c = '\0';

    /*
    // Check if file name was provided
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        makeFile(argv[1]);
    }
     */
    enableRawMode();        // Enable raw mode
    initEditor();           // Initialize editor

    // Read from terminal
    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }
}