//
// Created by xdanep on 2/12/23.
//

#ifndef TEXED_TERMINAL_H
#define TEXED_TERMINAL_H
#define CTRL_KEY(k) ((k) & 0x1f) // Bitwise AND operator

// Function prototypes
void disableRawMode();
void enableRawMode();
void die(const char *s);
#endif //TEXED_TERMINAL_H
