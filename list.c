/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <list.h>

list def_list;
list test_list;
list new_list();
void add(list l, void *data);
void* get(list l, size_t idx);
void set(list l, void *data, size_t idx);
void remove(list l, size_t idx);

list new_list() {
	def_list.first = smalloc(sizeof(node), 4);
	def_list.count = 0;
	def_list.add = add;
	def_list.get = get;
	def_list.set = set;
	def_list.instantiate = new_list;
	def_list.remove = remove;
	return def_list;
}

void add(list l, void *data)
{
	if(l.count < idx) {
		return;
	}
	node *n = l.first;
	node z = (node) smalloc(sizeof(node), 4);
	for(int i = 0; i < l.count; i++) {
		n = n->next;
	}
	count++;
	n->data = data;
	n->index = count;
	n->next = &z;
}

void* get(list l, size_t idx)
{
	if(l.count < idx) {
		return;
	}
	node *n = l.first;
	while(n->index != idx) {
		n = n->next;
	}
	return n->data;
}

void set(list l, void *data, size_t idx)
{
	if(l.count < idx) {
		return;
	}
	node *n = l.first;
	while(n->index != idx) {
		n = n->next;
	}
	n->data = data;
}

void remove(list l, size_t idx) //can cause memory overflow
{
	if(l.count < idx) {
		return;
	}
	node *n = l.first;
	while(n->index != (idx - 1)) {
		n = n->next;
	}
	node *prev = n;
	n = n->next;
	node *next = n->next;
	prev->next = next;
	(next->index)--;
	for(int i = idx; idx < l.count; i++) {
		n = n->next;
		(n->index)--;
	}
}