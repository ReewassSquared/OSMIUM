/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>

unsigned char* memcpy(void *dest, const void *src, size_t count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}

unsigned char* memset(void *dest, char val, size_t count)
{
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned short* memsetw(unsigned short *dest, unsigned short val, size_t count)
{
	unsigned short *temp = (unsigned short *)dest;
	for(; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned int* memsetd(unsigned int *dest, unsigned int val, size_t count)
{
	unsigned int *temp = (unsigned int *)dest;
	for(; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned char inb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

unsigned short inw (unsigned short _port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outw (unsigned short _port, unsigned short _data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (_port), "a" (_data));
}

unsigned int ind (unsigned short _port)
{
    unsigned int rv;
    __asm__ __volatile__ ("inl %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outd (unsigned short _port, unsigned int _data)
{
    __asm__ __volatile__ ("outl %1, %0" : : "dN" (_port), "a" (_data));
}

int strlen(const char *str)
{
	size_t c;
	for(c = 0; *str != '\0'; str++) c++;
	return c;
}

int cmd_strlen(unsigned char *cmd) //returns the first keyword in *cmd
{
	size_t c;
	char *tmp = *cmd;
	for(c = 0; *tmp != ' ' && *tmp != '\0'; tmp++) c++;
	return c;
}

int findchar(unsigned char *message, char ch)
{
	size_t c;
	for(c = 0; message[c] != ch; c++);
	return c;
}

bool strcmp(unsigned char *str1, unsigned char *str2)
{
	if(strlen(str1) != strlen(str2))
	{
		return false;
	}
	else
	{
		for( int y = 0; y < strlen(str2); y++)
		{
			if(*str1 != *str2)
			{
				return false;
			}
			str1++;
			str2++;
		}
	}
	return true;
}

bool cmd_strcmp(unsigned char *key, unsigned char *cmd, size_t offset)
{
	char *tmp = *cmd;
	for(int x = 0; x < offset; x++) {
		if(*key++ != *cmd++) {
			return false;
		}
	}
	return true;
}

void strcat(unsigned char *str1, unsigned char *str2, unsigned char *buffer) //note: str1 is added to the end of str2
{
	for(int x = 0; x < strlen(str1); x++)
	{
		*buffer = *str1;
		str1++;
		buffer++;
	}
	for(int x = 0; x < strlen(str2); x++)
	{
		*buffer = *str2;
		str2++;
		buffer++;
	}
}

bool strocc(unsigned char *strbig, unsigned char *strins)
{
	int h, g;
	bool r = false;
	if(strlen(strbig) > strlen(strins) ){
		return false;
	}
	for(g = 0; g < strlen(strbig); g++)
	{
		if(*strbig == *strins)
		{
			r = true;
			for(h = 0; h < strlen(strins); h++)
			{
				if(*strbig != *strins)
				{
					r = false;
					break;
				}
				strins++;
				strbig++;
			}
			if(r)
			{
				return true;
			}
		} 
		strins++;
		strbig++;
	}
	return false;
}

unsigned int strocc_times(unsigned char *strbig, unsigned char *strins)
{
	int h, g;
	int e = 0;
	bool r = false;
	for(g = 0; g < strlen(strbig); g++)
	{
		if(*strlen == *strins)
		{
			r = true;
			for(h = 0; h < strlen(strins); h++)
			{
				if(*strlen != *strins)
				{
					r = false;
					break;
				}
				strins++;
				strbig++;
			}
			if(r)
			{
				e++;
			}
			
		} 
		strins++;
		strbig++;
	}
	return e;
}

bool charocc(unsigned char *str, unsigned char f)
{
	for(int x = 0; x < strlen(str); x++)
	{
		if(*str++ = f)
		{
			return true;
		}
	}
	return false;
}

unsigned int charocc_times(unsigned char *str, unsigned char f)
{
	unsigned int ret = 0;
	for(int x = 0; x < strlen(str); x++)
	{
		if(*str++ = f)
		{
			ret++;
		}
	}
	return ret;
}

char* itoa(size_t val, size_t base){
	
	static char buf[32] = {0};
	
	short i = 30;

	if(val == 0)
	{
		return "0";
	}
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789ABCDEF"[val % base];
	
	for(int u = 0; u < 32; u++)
		buf[i] = 0;

	return &buf[i+1];
	
}

string num_to_string(size_t r, size_t base, unsigned char *buf)
{
	uint32_t temp = (uint32_t) buf;
	int g = 0;
	char convert[25] = {0};
	if( r == 0 )
	{
		buf[0] = '0';
	}
	else if(r < 0)
	{
		r  = -r;
		convert[g] = '-';
		g++;
	}
	int tmp = 0;
	while(r != 0)
	{
		tmp = r % base;
		if(tmp >= 36){
			convert[g] = (unsigned char) (61 + tmp);
		}
		else if(tmp >= 10)
		{
			convert[g] = (unsigned char) (55 + tmp);
		}
		else
		{
			convert[g] = (unsigned char) (tmp + 48);
		}
		r /= base;
		g++;
	}
	convert[g] = '\0';
	int x;
	int y = strlen(convert);
	convert[g] = 0;
	for(x = 0; x < strlen(convert); x++)
	{
		buf[y - x] = convert[x];
	}
	buf[y] = '\0';
	buf = (unsigned char *) temp;
	return buf;
}
/*
#define INT_DIGITS 19		// enough for 64 bit integer 

char *itoa(i)
     int i;
{
  // Room for INT_DIGITS digits, - and '\0' 
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	// points to terminating '\0' 
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			// i < 0 
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}
*/
string bool_to_string(bool r)
{
	if(r)
	{
		return "true";
	}
	return "false";
}

string removechar(string g, char r)
{
	int x = strlen(g) - charocc_times(g, r);
	int e = 0;
	char n[x];
	do
	{
		if(*g == r)
		{
			n[e] = g[e];
			e++;
		}
	} while(x != e);
	string str = r;
	return str;
}

string removestr(string g, string occ)
{
	int x = strlen(g) - strocc_times(g, occ);
	for(int e = 0; e < x; e++)
	{

	}
	//tmp
	return 0;
}
