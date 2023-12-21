//
// Created by xdanep on 2/12/23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "includes/file.h"
#include "includes/log.h"

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
            write_log("file.c: makeTextFile: Could not create file at the specified address.\n");
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
        write_log("file.c: overwriteFile: Could not create file at the specified address.\n");
        exit(EXIT_FAILURE);
    }
}

void createDirs(const char *dir)
{
    char *TEMP = ".temp.txt";

    // Create file directory
    fileDir = malloc(sizeof(char) * (strlen(dir) + 1));
    if (fileDir == NULL)
    {
        write_log("file.c: createDirs: Could not allocate memory for fileDir.\n");
        exit(EXIT_FAILURE);
    }
    if (strcpy(fileDir, dir) == NULL)
    {
        write_log("file.c: createDirs: Could not copy directory path to fileDir.\n");
        free(fileDir);
        exit(EXIT_FAILURE);
    }

    // Create temp file directory
    const char *lastSlash = strrchr(dir, '/');
    if (lastSlash != NULL)
    {
        size_t len = lastSlash - dir + 1;
        tempFile = malloc(sizeof(char) * (len + strlen(TEMP) + 1));
        if (tempFile == NULL)
        {
            write_log("file.c: createDirs: Could not allocate memory for tempFile.\n");
            free(fileDir);
            exit(EXIT_FAILURE);
        }
        if (strncpy(tempFile, dir, len) == NULL)
        {
            write_log("file.c: createDirs: Could not copy directory path to tempFile.\n");
            free(fileDir);
            free(tempFile);
            exit(EXIT_FAILURE);
        }
        tempFile[len] = '\0';
    }
    else
    {
        // Handle the case when there is no '/'
        tempFile = malloc(sizeof(char) * (strlen(dir) + strlen(TEMP) + 1));
        if (tempFile == NULL)
        {
            write_log("file.c: createDirs: Could not allocate memory for tempFile.\n");
            free(fileDir);
            exit(EXIT_FAILURE);
        }
        if (strcpy(tempFile, dir) == NULL)
        {
            write_log("file.c: createDirs: Could not copy directory path to tempFile.\n");
            free(fileDir);
            free(tempFile);
            exit(EXIT_FAILURE);
        }
    }

    // Concatenate TEMP to tempFile
    if (strcat(tempFile, TEMP) == NULL)
    {
        write_log("file.c: createDirs: Could not concatenate TEMP to tempFile.\n");
        free(fileDir);
        free(tempFile);
        exit(EXIT_FAILURE);
    }
}
