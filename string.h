/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef STRING_H
#define STRING_H
#include <stdbool.h>
#include <stdint.h>

typedef char *string;

extern unsigned char* memcpy(void *dest, const void *src, size_t count);
extern unsigned char* memset(void *dest, char val, size_t count);
extern unsigned short* memsetw(unsigned short *dest, unsigned short val, size_t count);
extern unsigned int* memsetd(unsigned int *dest, unsigned int val, size_t count);
extern unsigned char inb (unsigned short _port);
extern void outb (unsigned short _port, unsigned char _data);
extern unsigned short inw (unsigned short _port);
extern void outw (unsigned short _port, unsigned short _data);
extern unsigned int ind (unsigned short _port);
extern void outd (unsigned short _port, unsigned int _data);

extern int strlen(const char *str);
extern int strlen_cmd(const char *str);
extern bool strcmp(unsigned char *str1, unsigned char *str2);
extern bool cmd_strcmp(unsigned char *str1, unsigned char *cmd, size_t offset);
extern void strcat(unsigned char *str1, unsigned char *str2, unsigned char *buffer);
extern bool strocc(unsigned char *strbig, unsigned char *strins);
extern unsigned int strocc_times(unsigned char *strbig, unsigned char *strins);
extern string bool_to_string(bool r);
extern bool charocc(unsigned char *str, unsigned char f);
extern unsigned int charocc_times(unsigned char *str, unsigned char f);
extern string removechar(string g, char r);
extern char* itoa(size_t i, size_t base);

#endif
