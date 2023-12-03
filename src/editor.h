//
// Created by xdanep on 3/12/23.
//
#ifndef TEXED_EDITOR_H
#define TEXED_EDITOR_H
// Variables

// Function prototypes
// void abAppend(struct abuf *ab, const char *s, int len);
// void abFree(struct abuf *ab);
// void editorDrawRows(struct abuf *ab);
void editorRefreshScreen();
void initEditor();
void editorMoveCursor(char key);
char editorReadKey();
void editorProcessKeypress();
#endif //TEXED_EDITOR_H
