//
// Created by xdanep on 3/12/23.
//
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "includes/editor.h"
#include "includes/screen.h"
#include "includes/file.h"
#include "includes/cli.h"

WINDOW *texed; // Window
char *title;

void startScreen() {
    setlocale(LC_ALL, "");        // Set locale (es_MX.ISO-8859-1 or es_MX.UTF-8)
    initscr();                                  // Start curses mode
    E.x = 0;                                    // set the x position
    E.y = 0;                                    // set the y position
    E.nRows = 0;
    E.wRows = NULL;

    // Initialize a new window
    raw();                                      // enter raw mode
    keypad(stdscr, TRUE);                       // Obtain F1, F2 etc...
    cbreak();                                   // Line buffering disabled
    noecho();                                   // No echo input
    getmaxyx(stdscr, E.rows, E.cols);           // get the screen size

    texed = newwin(E.rows, E.cols, 0, 0);      // Create a new window

    if (start_color() == ERR || !has_colors() || !can_change_color()) // start color
    {
        endwin(); // close ncurses
        refresh();

        fputs("Could not use colors.", stderr);

        exit(EXIT_FAILURE);
    }
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // set white text on black background
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // set black text on white background
    wattron(texed, COLOR_PAIR(1)); // apply color's configuration

    wrefresh(texed);                           // print on the screen
    getch();                                    // Wait for user input
}

void screenInfo() {
    title = malloc(sizeof(char) * (strlen("Texed - ")));
    memcpy(title, "Texed - ", strlen("Texed - "));

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(VERSION)));   // Allocate memory

    if(title == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, VERSION);

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(" - ")));   // Allocate memory

    if(title == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, " - ");

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(fileDir)));   // Allocate memory

    if(title == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, fileDir);
}