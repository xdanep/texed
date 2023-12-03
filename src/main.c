//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "files.h"
#include "terminal.h"

// Display keypresses
int main(int argc, char *argv[]) {
    // Variables
    char c;

    // Check if file name was provided
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        makeFile(argv[1]);
    }
    enableRawMode();        // Enable raw mode

    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        fprintf(fileIn, "%c", c);
    }
    // Close file
    fclose(fileIn);
    exit(EXIT_SUCCESS);
}