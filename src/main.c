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

int main(int argc, char *argv[]) {
    // Variables
    char c = '\0';

    // Check if file name was provided
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        makeFile(argv[1]);
    }
    enableRawMode();        // Enable raw mode

    // Read from terminal
    while(1) {
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");      // Read character from terminal

        // Check if character is a control character
        if (iscntrl(c)) {
            printf("%d\r\n", c);          // Print ASCII code
        } else {
            printf("%d ('%c')\r\n", c, c); // Print ASCII code and character
        }
        if(c == 'q') break;             // Exit loop if 'q' is pressed
        // fprintf(fileIn, "%c", c); // Write to file
    }
    // Close file
    fclose(fileIn);
    exit(EXIT_SUCCESS);
}