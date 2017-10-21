/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <static_memalloc.h>

uint8_t *base_smalloc_address = 0x00200000;
uint32_t availability_offset = 0;

void* smalloc(size_t size, size_t align)
{
	if(availability_offset == 0x00100000) {
		return -1;
	}
	availability_offset += (((uint32_t) size & (~((uint32_t) align-1)) ));
	return (uint8_t *) ((uint32_t) base_smalloc_address + availability_offset);
}
