//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "includes/file.h"

FILE *fileIn;

// Read or create file
unsigned int makeTextFile(const char *dir)
{
    // Open file in read mode
    if ((fileIn = fopen(dir, "r")) == NULL)
    {
        // Open file in write mode
        fileIn = fopen(dir, "w");

        // Verify file
        if (fileIn == NULL)
        {
            fprintf(stderr, "Error: Could not create file at the specified address.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        return 0; // Read mode
    }
    return 1; // Write mode
}

void overwriteFile(const char *dir)
{
    // Open file in write mode
    fileIn = fopen(dir, "w");

    // Verify file
    if (fileIn == NULL)
    {
        fprintf(stderr, "Error: Could not create file at the specified address.\n");
        exit(EXIT_FAILURE);
    }
}

void createDirs(const char *dir)
{
    char *TEMP = "/.temp.txt";
    // Create file directory
    fileDir = malloc(sizeof(char) * strlen(dir));
    memcpy(fileDir, dir, strlen(dir));
    fileDir[strlen(dir)] = '\0';

    // Create temp file directory
    for (unsigned long i = strlen(dir); i > 0; i--)
    {
        if (dir[i] == '/')
        {
            tempFile = malloc(sizeof(char) * i);
            memcpy(tempFile, dir, i);
            tempFile[strlen(tempFile)] = '\0';
            break;
        }
    }

    tempFile = realloc(tempFile, sizeof(char) * (strlen(tempFile) + sizeof(char) * strlen(TEMP)));
    if (tempFile == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for tempFile.\n");
        exit(EXIT_FAILURE);
    }
    strcat(tempFile, TEMP);
}