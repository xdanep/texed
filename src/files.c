//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "files.h"

FILE *fileIn;

// Creating a file
void makeFile(char *dir) {
    // Open file with write permission
    fileIn = fopen(dir, "w");

    // Check if file was created
    if (fileIn == NULL) {
        fprintf(stderr,"Error: Could not open file %s\n", dir);
        exit(EXIT_FAILURE);
    } else {
        fprintf(stdout,"File %s created successfully\n", dir);
    }
}