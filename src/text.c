//
// Created by xdanep on 13/12/23.
//

#include <stdlib.h>
#include <string.h>
#include "includes/text.h"
#include "includes/file.h"
#include "includes/screen.h"

// Taken from https://github.com/snaptoken/kilo-src
void editorAppendRow(char *s, size_t len) {
    E.wRows = realloc(E.wRows, sizeof(writtenRows) * (E.nRows + 1));
    if(E.wRows == NULL) exit(EXIT_FAILURE);

    int at = E.nRows;
    E.wRows[at].length = len;
    E.wRows[at].wText = malloc(len + 1);
    memcpy(E.wRows[at].wText, s, len);
    E.wRows[at].wText[len] = '\0';
    E.nRows++;
}

// Insert new line at the given position
void editorInsertRow(int at, char *s, size_t len) {
    if (at < 0 || at > E.nRows) exit(EXIT_FAILURE);

    // Allocate memory for new line
    E.wRows = realloc(E.wRows, sizeof(writtenRows) * (E.nRows + 1));
    if(E.wRows == NULL) exit(EXIT_FAILURE);

    // Move lines below new line
    memmove(&E.wRows[at + 1], &E.wRows[at], sizeof(writtenRows) * (E.nRows - at));

    // Insert new line
    E.wRows[at].length = len;
    E.wRows[at].wText = malloc(len + 1);
    memcpy(E.wRows[at].wText, s, len);
    E.wRows[at].wText[len] = '\0';

    E.wRows[at].rsize = 0;
    E.wRows[at].render = NULL;
    editorUpdateRow(&E.wRows[at]);

    // Update number of rows
    E.nRows++;
}

// Taken from https://github.com/snaptoken/kilo-src
void editorUpdateRow(writtenRows *row) {
    int tabs = 0;
    int j;
    for (j = 0; j < row->length; j++)
        if (row->wText[j] == '\t') tabs++;

    free(row->render);
    row->render = malloc(row->length + tabs*(KILO_TAB_STOP - 1) + 1);
    if(row->render == NULL) exit(EXIT_FAILURE);

    int idx = 0;
    for (j = 0; j < row->length; j++) {
        if (row->wText[j] == '\t') {
            row->render[idx++] = ' ';
            while (idx % KILO_TAB_STOP != 0) row->render[idx++] = ' ';
        } else {
            row->render[idx++] = row->wText[j];
        }
    }
    row->render[idx] = '\0';
    row->rsize = idx;
}

// Taken from https://github.com/snaptoken/kilo-src
void editorRowInsertChar(writtenRows *row, int at, int c) {
    if (at < 0 || at > row->length) at = row->length;

    row->wText = realloc(row->wText, row->length + 2);
    if(row->wText == NULL) exit(EXIT_FAILURE);

    memmove(&row->wText[at + 1], &row->wText[at], row->length - at + 1);
    row->length++;
    row->wText[at] = c;
    editorUpdateRow(row);
}

// Taken from https://github.com/snaptoken/kilo-src
void editorInsertChar(int c) {
    if (E.y == E.nRows) {
        editorAppendRow("", 0);
    }
    editorRowInsertChar(&E.wRows[E.y], E.x, c);
}

// Remove line and add it at the end of the previous line
void removeLine() {
    // Add next line to current line
    E.wRows[E.y].wText = realloc(E.wRows[E.y].wText, E.wRows[E.y].length + E.wRows[E.y + 1].length + 1);
    if(E.wRows[E.y].wText == NULL) exit(EXIT_FAILURE);

    memmove(&E.wRows[E.y].wText[E.wRows[E.y].length],
            E.wRows[E.y + 1].wText, E.wRows[E.y + 1].length); // Copy next line to current line
    E.wRows[E.y].length += E.wRows[E.y + 1].length;                 // Update length
    E.wRows[E.y].wText[E.wRows[E.y].length] = '\0';                 // Add end of line

    // Update rows
    memmove(&E.wRows[E.y + 1], &E.wRows[E.y + 2], sizeof(writtenRows) * (E.nRows - E.y - 2));

    // Reallocate memory
    E.wRows = realloc(E.wRows, sizeof(writtenRows) * (E.nRows - 1));
    if(E.wRows == NULL) exit(EXIT_FAILURE);

    // Update number of rows
    E.nRows--;
}