/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <print.h>

uint32_t xpos = 0;
uint32_t ypos = 0;
uint32_t color = DEFAULT_COLOR;
short *scrnlibptr = 0xB8000;

void set_color(short c)
{
	color = c;
}

void get_color(short *c)
{
	*c = color;
}

void get_cursor_pos(size_t *xp, size_t *yp)
{
	*xp = xpos;
	*yp = ypos;
}

void scroll(void)
{
	if(ypos >= TERMINAL_Y)
	{
		tmp = ypos - TERMINAL_Y + 1;
		memcpy(screenptr, screenptr + tmp * TERMINAL_X, (TERMINAL_Y - tmp) * 2 * TERMINAL_X);
		memsetw(screenptr + ((TERMINAL_Y - tmp) * TERMINAL_X), color | 0x0020, TERMINAL_X);
		
		ypos = TERMINAL_Y - 1;
	}
}

void putc(char c)
{
	short *a = (short *) ((uint32_t) scrnlibptr + xpos + (ypos * TERMINAL_X));
	if(c == 0x08){ 
		if(xpos == 0 && ypos == 0) 
		{		
			return;
		}
		else if(xpos == 0)
		{
			xpos = TERMINAL_X - 1;
			ypos--;
			a[x] = (short) color | 0x0020;
		}
	}
	else if(c == 0x09){
		if(xpos >= TERMINAL_X - 1) {
			x = 0;
			y++;
		}
		for(; xpos < xpos + (8 - (xpos % 8)); xpos++ ) {
			*a = (short) color | 0x0020;
			*a++;
		}
	}
	else if(c == '\r'){
		xpos = 0;
	}
	else if(c == '\n'){
		xpos = 0;
		ypos++;
	}
	else {
		*a = (short) c | DEFAULT_COLOR;
		xpos++;
		if(xpos >= 80) {
			ypos++;
			xpos = 0;
		}	
	}
	scroll();
}

void puts(char *c)
{
	printf(c);
}

void println(char *c)
{
	printf("%s%c", c, '\n');
}

void vprintf(char *c, va_list args)
{
	for(int x = 0; x < strlen(c); x++) {
		if(c[x] == '%') {
			x++;
			switch c[x] {
				case 's':
					char *str = va_arg(args, char*);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'c':
					char chr = va_arg(args, char);
					putc(chr);
					break;
				case '%':
					putc('%');
					break;
				case 'd':
					size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					char *str = itoa(integer, 10);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'i':
					size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					char *str = itoa(integer, 10);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'x':
					size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					putc('0');
					putc('x');
					char *str = itoa(integer, 16);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'X':
				size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					putc('0');
					putc('x');
					char *str = itoa(integer, 16);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'o':
					size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					putc('0');
					putc('o');
					char *str = itoa(integer, 8);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				case 'O':
					size_t integer = va_arg(args, size_t);
					if(integer > 0x80000000) {
						putc('-');
						integer = ~(integer) - 1;
					}
					putc('0');
					putc('o');
					char *str = itoa(integer, 8);
					for(int i = 0; i < strlen(str); i++) {
						putc(str[i]);
					}
					break;
				default:
					putc(c[x]);
			}
		}
		else {
			putc(c[x]);
		}
	}
}

void printf(char *c, ...)
{
	va_list args;
	va_start(args, c);
	vprintf(c, args);
	va_end(args);
}