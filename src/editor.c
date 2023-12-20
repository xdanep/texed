//
// Created by xdanep on 3/12/23.
//
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "includes/editor.h"
#include "includes/screen.h"
#include "includes/file.h"
#include "includes/text.h"

EditConfig E; // Window size

void writeEditor(unsigned int mode)
{
    int c; // Character and iterator

    initEditor(mode); // Initialize editor
    saveFile();       // Save in temp file

    do
    {
        c = getch();        // get character
        inputKeyProcess(c); // process character
    } while (1);            // exit if the character is ctrl + x
}

// Taken from https://github.com/snaptoken/kilo-src
void readEditor(FILE *tfile)
{
    char *strings = NULL; // String pointer
    size_t linecap = 0;   // Length
    ssize_t linelen;      // Line length

    while ((linelen = getline(&strings, &linecap, tfile)) != -1)
    {
        while (linelen > 0 && (strings[linelen - 1] == '\n' ||
                               strings[linelen - 1] == '\r'))
        {
            linelen--; // Remove new line
        }
        editorAppendRow(strings, linelen); // Append row
    }
    free(strings); // Free memory
    fclose(tfile); // Close file
}

// Print file content on screen
void editorPrint()
{
    wattron(texed, COLOR_PAIR(2)); // apply color's configuration
    mvwprintw(texed, 0, E.cols / 2 - strlen(title) / 2, "%s", title);
    mvwprintw(texed, E.rows - 1, 0, "^X Exit  ^S Save");
    wattron(texed, COLOR_PAIR(1)); // apply color's configuration
    wmove(texed, 1, 0);            // Move cursor to the first position

    if (E.nRows < E.rows - 1)
    {
        for (E.y = 0; E.y < E.nRows; E.y++)
        {
            // Print line larger than the window
            if (E.wRows[E.y].length >= E.cols)
            {
                for (E.x = 0; E.x < E.cols; E.x++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.x]);
                }
            }
            // Print line smaller than the window
            else
            {
                for (E.x = 0; E.x < E.wRows[E.y].length; E.x++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.x]);
                }
                // Add new line
                if (E.wRows[E.y].wText[E.wRows[E.y].length - 1] != '\n')
                    waddch(texed, '\n');
                else
                    continue;
            }
        }
    }
    else
    {
        for (E.y = E.fy; E.y - E.fy < E.rows - 2; E.y++)
        {
            // Print line larger than the window
            if (E.wRows[E.y].length >= E.cols)
            {
                for (E.x = 0; E.x < E.cols; E.x++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.x]);
                }
            }
            // Print line smaller than the window
            else
            {
                for (E.x = 0; E.x < E.wRows[E.y].length; E.x++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.x]);
                }
                // Add new line
                if (E.wRows[E.y].wText[E.wRows[E.y].length - 1] != '\n')
                    waddch(texed, '\n');
                else
                    continue;
            }
        }
    }
}

void printChar()
{
    // Print changes
    if (E.wRows[E.y].length < E.cols)
    {

        wmove(texed, E.sy, 0);              // Move cursor to the first position
        wclrtoeol(texed);                   // Clear line
        wprintw(texed, E.wRows[E.y].wText); // Print line
    }
    else if (E.wRows[E.y].length >= E.cols && E.x >= E.cols)
    {
        // if(E.x == E.cols) E.sy--;
        wmove(texed, E.sy, 0); // Move cursor to the first position
        wclrtoeol(texed);      // Clear line

        // Print line
        for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
        {
            waddch(texed, E.wRows[E.y].wText[E.sx]);
        }
    }
    else if (E.wRows[E.y].length >= E.cols && E.x < E.cols)
    {
        wmove(texed, E.sy, 0); // Move cursor to the first position
        wclrtoeol(texed);      // Clear line

        // Print line
        for (E.sx = 0; E.sx < E.cols; E.sx++)
        {
            waddch(texed, E.wRows[E.y].wText[E.sx]);
        }
    }
    // Restore cursor position
    E.x++;
    E.sy = E.y + 1;
    if (E.x < E.cols)
        E.sx = E.x;
    else if (E.x >= E.cols)
        E.sx = E.x - E.cols;
    wmove(texed, E.sy, E.sx); // Move cursor
}

void saveFile()
{
    // Print in file
    FILE *TEMP = fopen(tempFile, "w");
    if (TEMP == NULL)
    {
        fprintf(stderr, "Error: Could not create file at the specified address.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < E.nRows; i++)
    {
        fprintf(TEMP, "%s", E.wRows[i].wText);
        if (E.wRows[i].wText[E.wRows[i].length - 1] != '\n')
        {
            fprintf(TEMP, "\n");
        }
    }
    fclose(TEMP);
}

void initEditor(unsigned int mode)
{
    // Print file content on screen
    if (mode == 0)
    {
        editorPrint();   // Print content
        wrefresh(texed); // Refresh window

        // Move cursor to the first position
        E.y = 0;
        E.x = 0;
        E.sy = E.y + 1;
        E.fy = 0;
        E.sx = E.x;
        wmove(texed, E.sy, E.sx); // Move cursor
        wrefresh(texed);          // Refresh window
    }
    else if (mode == 1)
        editorAppendRow("", 0); // Insert first line

    else
    {
        fprintf(stderr, "Error: Invalid mode.\n");
        exit(EXIT_FAILURE);
    }
}

void exitEditor()
{
    mvwprintw(texed, E.rows - 1, 0, "Do you want to save the file? (y/n): ");
    wrefresh(texed);

    int c = getch();
    waddch(texed, c);
    wrefresh(texed);

    if (c == 'n' || c == 'N')
    {
        if (remove(fileDir) != 0)
            perror("Error deleting file"); // Remove TEMP
        if (rename(tempFile, fileDir) != 0)
            perror("Error renaming file"); // Rename TEMP to file
    }
    else
    {
        // Print in file
        for (int i = 0; i < E.nRows; i++)
        {
            fprintf(fileIn, "%s", E.wRows[i].wText);
            if (E.wRows[i].wText[E.wRows[i].length - 1] != '\n')
            {
                fprintf(fileIn, "\n");
            }
        }
        // Remove TEMP
        if (remove(tempFile) != 0)
            perror("Error deleting file");
    }

    free(E.wRows);  // Free memory
    wclear(texed);  // Clear window
    endwin();       // End curses mode
    fclose(fileIn); // Close file

    free(fileDir);      // Free memory
    free(tempFile);     // Free memory
    exit(EXIT_SUCCESS); // Exit
}

void inputKeyProcess(int c)
{
    int tx, ty; // Temporary x and y

    // If the character is backspace or delete
    if (c == KEY_BACKSPACE || c == 127)
    {
        // Verify if we are on the first position
        if (E.x > 0)
        {
            // Move the cursor to the left
            E.x--;
            E.sx--;
            if (E.x == E.cols - 1)
            {
                wmove(texed, E.sy, 0); // Move cursor to the first position
                wclrtoeol(texed);      // Clear line

                // Print line
                for (E.sx = 0; E.sx < E.cols; E.sx++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.sx]);
                }
                E.sx = E.x;
            }
            wmove(texed, E.sy, E.sx);

            wdelch(texed); // Delete actual character on screen

            // Delete actual character on memory
            memmove(&E.wRows[E.y].wText[E.x], &E.wRows[E.y].wText[E.x + 1], E.wRows[E.y].length - E.x);
            E.wRows[E.y].wText = realloc(E.wRows[E.y].wText, E.wRows[E.y].length);
            if (E.wRows[E.y].wText == NULL)
                exit(EXIT_FAILURE);

            E.wRows[E.y].length--;
            editorUpdateRow(&E.wRows[E.y]);
        }
        else if (E.x == 0 && E.y > 0)
        {
            // Move to the previous line
            E.y--;
            E.sy--;
            E.x = E.wRows[E.y].length;

            // Remove line
            removeLine();
            editorUpdateRow(&E.wRows[E.y]);

            // Save cursor position
            tx = E.x;
            ty = E.y;
            wmove(texed, E.sy, E.sx);

            wclear(texed); // Delete actual character
            editorPrint(); // Print content

            // Restore cursor position
            E.x = tx;
            E.y = ty;
            E.sy = E.y + 1;

            // Line is larger than the window
            if (E.x >= E.cols)
            {
                wmove(texed, E.sy, 0); // Move cursor to the first position
                wclrtoeol(texed);      // Clear line
                for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.sx]);
                }
                E.sx = E.x - E.cols;
            }
            else
                E.sx = E.x;
            wmove(texed, E.sy, E.sx);
        }
    }
    else if (c == KEY_ENTER || c == 13 || c == 10)
    {
        // Cursor moves to the next line
        E.y++;
        E.sy++;

        if (E.y <= E.nRows && E.x != E.wRows[E.y - 1].length)
        {
            // Save cursor position
            ty = E.y;

            // Insert new line
            editorInsertRow(E.y, "", 0);
            E.wRows[E.y].wText = realloc(E.wRows[E.y].wText, E.wRows[E.y - 1].length - E.x);          // Allocate memory
            strncpy(E.wRows[E.y].wText, &E.wRows[E.y - 1].wText[E.x], E.wRows[E.y - 1].length - E.x); // Copy text
            E.wRows[E.y].length = E.wRows[E.y - 1].length - E.x;                                      // Update length
            E.wRows[E.y - 1].length = E.x;                                                            // Update length
            E.wRows[E.y - 1].wText[E.x] = '\0';                                                       // Add end of line
            E.wRows[E.y].wText[E.wRows[E.y].length] = '\0';                                           // Add end of line
            editorUpdateRow(&E.wRows[E.y]);
            editorUpdateRow(&E.wRows[E.y - 1]);

            wclear(texed); // Clear window
            editorPrint(); // Print content

            // Restore cursor position
            E.y = ty;
            E.sy = E.y + 1;
        }
        else if (E.y <= E.nRows && E.x == E.wRows[E.y - 1].length)
        {
            // Save cursor position
            ty = E.y;

            // Insert new line
            editorInsertRow(E.y, "", 0);
            editorUpdateRow(&E.wRows[E.y]);

            wclear(texed);
            editorPrint();

            // Restore cursor position
            E.y = ty;
            E.sy = E.y + 1;
        }
        else
        {
            // Append new line
            editorAppendRow("", 0);
            editorUpdateRow(&E.wRows[E.y]);

            wclear(texed); // Clear window
            editorPrint(); // Print content

            // Move cursor
            E.y = E.nRows - 1;
            E.sy = E.y + 1;
        }
        E.x = 0;
        E.sx = E.x;
        wmove(texed, E.sy, E.sx);

        // If the character is left
    }
    else if (c == KEY_LEFT)
    {
        // Move cursor to the left
        E.x--;
        E.sx--;

        // If the cursor is on the first position
        if (E.x < 0 && E.y > 0)
        {
            E.y--;
            E.sy--;
            // Reprint current line
            if (E.wRows[E.y].length >= E.cols)
            {
                wmove(texed, E.sy, 0); // Move cursor to the first position
                wclrtoeol(texed);      // Clear line

                // Print line
                for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.sx]);
                }
            }
            E.x = E.wRows[E.y].length;
            E.sx = E.x;
        }
        // Move to the previows screen
        if (E.x == E.cols - 1)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = 0; E.sx < E.cols; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
            E.sx = E.x;
        }
        wmove(texed, E.sy, E.sx);
    }
    else if (c == KEY_RIGHT)
    {
        // Move cursor to the right
        E.x++;
        E.sx++;

        // If the cursor is on the last position
        if (E.x > E.wRows[E.y].length && E.y < E.nRows - 1)
        {
            // Reprint current line
            if (E.wRows[E.y].length >= E.cols)
            {
                wmove(texed, E.sy, 0); // Move cursor to the first position
                wclrtoeol(texed);      // Clear line

                // Print line
                for (E.sx = 0; E.sx < E.cols; E.sx++)
                {
                    waddch(texed, E.wRows[E.y].wText[E.sx]);
                }
            }
            E.y++;
            E.sy++;
            E.x = 0;
            E.sx = E.x;
        }

        // Move to the next line
        else if (E.x > E.wRows[E.y].length && E.y == E.nRows - 1)
        {
            E.x = E.wRows[E.y].length;
            E.sx = E.x;
        }

        // Move to the next screen
        if (E.sx == E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
            E.sx = E.x - E.cols;
        }
        wmove(texed, E.sy, E.sx);
    }
    else if (c == KEY_DOWN)
    {
        // Reprint current line
        if (E.x >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = 0; E.sx < E.cols; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
        }
        // Move cursor to the next line
        E.y++;
        E.sy++;
        // Move screen to the next line
        if(E.sy >= E.rows - 1 && E.y < E.nRows)
        {
            ty = E.y;
            tx = E.x;
            E.fy++;
            wclear(texed); // Clear window
            editorPrint(); // Print content
            E.y = ty;
            E.x = tx;
            E.sy = E.rows - 2;
        }
        // Repair cursor position
        if (E.y >= E.nRows)
        {
            E.y = E.nRows - 1;
            E.sy = E.y + 1;
        }
        // If previows line is larger than current line
        if (E.wRows[E.y].length < E.x)
        {
            E.x = E.wRows[E.y].length;
            E.sx = E.x;
        }

        // Line is larger than the window
        if (E.x >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
            E.sx = E.x - E.cols;
        }
        wmove(texed, E.sy, E.sx);
    }
    else if (c == KEY_UP)
    {
        // Reprint current line
        if (E.x >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = 0; E.sx < E.cols; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
        }
        // Move cursor to the previous line
        E.y--;
        E.sy--;
        // Move screen to the next line
        if(E.sy <= 0 && E.y >= 0)
        {
            ty = E.y;
            tx = E.x;
            E.fy--;
            wclear(texed); // Clear window
            editorPrint(); // Print content
            E.y = ty;
            E.x = tx;
            E.sy = 1;
        }

        // If the cursor is on the first position
        if (E.y < 0)
        {
            E.y = 0;
            E.sy = E.y + 1;
        }

        // If previows line is larger than current line
        if (E.wRows[E.y].length < E.x)
        {
            E.x = E.wRows[E.y].length;
            E.sx = E.x;
        }

        // Line is larger than the window
        if (E.x >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
            E.sx = E.x - E.cols;
        }
        wmove(texed, E.sy, E.sx);
    }
    else if (c == KEY_END)
    {
        // End of page
        // Reprint current line
        if (E.wRows[E.y].length >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = 0; E.sx < E.cols; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
        }
        // Move cursor to the end of the page
        E.y = E.nRows - 1;
        E.sy = E.y + 1;
        // Reprint line
        if (E.wRows[E.y].length >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = E.cols; E.sx < E.wRows[E.y].length; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
        }
        E.x = E.wRows[E.y].length;
        E.sx = E.x;
        wmove(texed, E.sy, E.sx);
    }
    else if (c == KEY_HOME)
    {
        // Start of page
        // Reprint line
        if (E.wRows[E.y].length >= E.cols)
        {
            wmove(texed, E.sy, 0); // Move cursor to the first position
            wclrtoeol(texed);      // Clear line

            // Print line
            for (E.sx = 0; E.sx < E.cols; E.sx++)
            {
                waddch(texed, E.wRows[E.y].wText[E.sx]);
            }
        }
        // Move cursor to the start of the page
        E.y = 0;
        E.sy = E.y + 1;
        E.x = 0;
        E.sx = E.x;
        wmove(texed, E.sy, E.sx);
    }
    else if (c == CTRL_KEY('s'))
    {
        // Save
        saveFile();
    }
    else if (c == CTRL_KEY('x'))
    {
        // Exit
        exitEditor();
    }
    else
    {
        // If the character is a letter print and add the character
        // Insert and print changes
        editorInsertChar(c);
        editorUpdateRow(&E.wRows[E.y]);
        printChar();
    }
    wrefresh(texed);          // refresh the window
    getyx(texed, E.sy, E.sx); // get cursor position
}