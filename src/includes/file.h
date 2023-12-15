//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>

#ifndef TEXED_FILE_H
#define TEXED_FILE_H
// Variables
extern FILE *fileIn;
extern char *fileDir;
extern char *tempFile;

// Functions
unsigned int makeTextFile(const char *dir);     // Read or create file
void overwriteFile(const char *dir);            // Overwrite file
void createDirs(const char *dir);                          // Create dirs
#endif //TEXED_FILE_H
