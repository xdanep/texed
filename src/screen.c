//
// Created by xdanep on 3/12/23.
//
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "includes/editor.h"
#include "includes/screen.h"
#include "includes/file.h"
#include "includes/version.h"
#include "includes/log.h"

struct termios original_state;
char *title;

void startScreen()
{
    if (tcgetattr(STDIN_FILENO, &original_state) == -1)
    {
        write_log("screen.c: startScreen: Could not getting terminal attributes");
        exit(EXIT_FAILURE);
    }
    
    // Initialize a new window
    setlocale(LC_ALL, ""); // Set locale (es_MX.ISO-8859-1 or es_MX.UTF-8)
    initscr();             // Start curses mode
    E.x = 0;               // set the x position
    E.y = 0;               // set the y position
    E.nRows = 0;
    E.wRows = NULL;
    
    raw();                            // enter raw mode
    keypad(stdscr, TRUE);             // Obtain F1, F2 etc...
    cbreak();                         // Line buffering disabled
    noecho();                         // No echo input
    getmaxyx(stdscr, E.rows, E.cols); // get the screen size

    if (start_color() == ERR || !has_colors() || !can_change_color()) // start color
    {
        endwin(); // close ncurses
        refresh();

        write_log("screen.c: startScreen: Could not use colors.");

        exit(EXIT_FAILURE);
    }
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // set white text on black background
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // set black text on white background
    attron(COLOR_PAIR(1));          // apply color's configuration
}

void screenInfo()
{
    title = malloc(sizeof(char) * (strlen("Texed - ")));
    memcpy(title, "Texed - ", strlen("Texed - "));

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(VERSION))); // Allocate memory

    if (title == NULL)
    {
        write_log("screen.c: screenInfo: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, VERSION);

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(" - "))); // Allocate memory

    if (title == NULL)
    {
        write_log("screen.c: screenInfo: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, " - ");

    title = realloc(title, sizeof(char) * (strlen(title) + strlen(fileDir))); // Allocate memory

    if (title == NULL)
    {
        write_log("screen.c: screenInfo: Could not allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }
    strcat(title, fileDir);
}

void restore_terminal_state()
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, &original_state) == -1)
    {
        write_log("screen.c: restore_terminal_state: Could not setting terminal attributes");
        exit(EXIT_FAILURE);
    }
}
