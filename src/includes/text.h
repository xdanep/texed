//
// Created by xdanep on 13/12/23.
//
#include "editor.h"

#ifndef TEXED_TEXT_H
#define TEXED_TEXT_H
// Defines
#define KILO_TAB_STOP 8

// Function prototypes
void editorAppendRow(char *s, size_t len);
void editorInsertRow(int at, char *s, size_t len);
void editorUpdateRow(writtenRows *row);
void editorRowInsertChar(writtenRows *row, int at, int c);
void editorInsertChar(int c);
void removeLine();
#endif // TEXED_TEXT_H
