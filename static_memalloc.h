/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef STATIC_MEMALLOC_H
#define STATIC_MEMALLOC_H
#include <stdlib.h>

extern uint8_t *base_smalloc_address;
extern uint32_t availability_offset;

extern void* malloc(size_t size, size_t align);

#endif