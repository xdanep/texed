//
// Created by xdanep on 12/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/cli.h"
#include "includes/version.h"

void checkArgs(int argc, char **argv)
{

    if (argc == 1)
    {
        // No arguments
        fprintf(stderr, "Use: %s --help\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (argc == 2)
    {
        // One argument
        if (strcmp(argv[1], "--version") == 0)
        {
            // Print version number
            printf("Texed version %s\n", VERSION);
            printf("Copyright Xdanep and Aarch64 (C) 2023\n");
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[1], "--help") == 0)
        {
            // Print help
            printf("Usage: %s <filename>\n", argv[0]);
            printf("Options:\n");
            printf("--version\t\t\tShow version number\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            return;
        }
    }
    else if (argc > 2)
    {
        // Too many arguments
        fprintf(stderr, "Error: Too many arguments.\n");
        exit(EXIT_FAILURE);
    }
}
