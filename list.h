/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef LIST_H
#define LIST_H
#include <static_memalloc.h>

typedef struct __attribute__ ((packed)) node {
	void *data;
	uint32_t index;
	node *next;
} node;

typedef struct __attribute__ ((packed)) list {
	node *first;
	uint32_t count;

	void (*add)(list, void*);
	void* (*get)(list, size_t);
	void (*set)(list, void*, size_t);
	void (*remove)(list, size_t);
	list (*instantiate)();
} list;

extern list def_list;
extern list test_list;
extern list new_list();
extern void add(list l, void *data);
extern void* get(list l, size_t idx);
extern void set(list l, void *data, size_t idx);
extern void remove(list l, size_t idx);

#endif