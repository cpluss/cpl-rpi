#ifndef CONSOLE_H
#define CONSOLE_H

#include "types.h"

/*
 This is basically simple console output, to render
 characters in a better way...
  */
typedef struct {
    uint x, y; //Current cursor position
    uint width, height; //Bounds of the console
    uint flags; //Reserved for future purposes
} console_t;

/* Initialize the console */
void console_init(uint width, uint height);

/* Print a character to the screen */
void console_putc(char c);

/* Print a string */
void console_puts(const char *s);

#endif
