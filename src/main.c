//
// Created by xdanep on 9/11/23.
//
#include <string.h>
#include "includes/file.h"
#include "includes/editor.h"
#include "includes/screen.h"
#include "includes/cli.h"

char *fileDir = NULL;
char *tempFile = NULL;

int main(int argc, char *argv[]) {
    unsigned int mode;              // Mode

    checkArgs(argc, argv);          // Check arguments
    createDirs(argv[1]);

    // Create file
    mode = makeTextFile(fileDir);

    startScreen();                  // Start screen
    screenInfo();                   // Generate screen info

    if(mode == 1) writeEditor(mode);      // Run editor write mode
    else if(mode == 0) {
        readEditor(fileIn); // Run editor read mode
        overwriteFile(fileDir);
        writeEditor(mode); // Run editor write mode
    }
}