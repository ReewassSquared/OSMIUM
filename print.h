/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef PRINT_H
#define PRINT_H
#define TERMINAL_X 80
#define TERMINAL_Y 25
#define DEFAULT_COLOR 0x0F00
#include <stdlib.h>
#include <string.h>

extern short *scrnlibptr = 0xB8000;
extern void set_color(short c)
extern void get_color(short *c);
extern void get_cursor_pos(size_t *xp, size_t *yp);
extern void putc(char c);
extern void puts(char *c);
extern void println(char *c);
extern void printf(char *c, ...);
extern void vprintf(char *c, va_list args);

#endif