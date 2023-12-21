//
// Created by xdanep on 3/12/23.
//
#include <stdio.h>

#ifndef TEXED_EDITOR_H
#define TEXED_EDITOR_H
// Variables
#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct
{
    int length;   // text size
    int rsize;    // render size
    char *wText;  // Written text
    char *render; // Rendered text
} writtenRows;

typedef struct
{
    int x;              // Cursor position
    int y;              // Cursor position
    int sx, sy;         // Screen position
    int fy;             // First y position of the screen
    int rows;           // Screen raws
    int cols;           // Screen columns
    int nRows;          // Number of written raws
    writtenRows *wRows; // Text in rows
} EditConfig;
extern EditConfig E;

// Function prototypes
void writeEditor(unsigned int mode);
void readEditor(FILE *tfile);
void editorPrint();
void printChar();
void saveFile();
void initEditor(unsigned int mode);
void exitEditor();
void inputKeyProcess(int c);
#endif // TEXED_EDITOR_H
