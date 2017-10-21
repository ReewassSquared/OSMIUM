/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <graphics.h>

menu menu_instantiate(uint32_t size_x, uint32_t size_y, uint16_t *data); 
menu new_menu(uint32_t size_x, uint32_t size_y, uint16_t *data);
void menu_deconstruct(menu *m);
void def_menu_update(menu *m);

button def_button;
button test_button;

button new_button(uint32_t loc_x, uint32_t loc_y, uint32_t length, void (*on_press)(button*))
{
	def_button.loc_x = loc_x;
	def_button.loc_y = loc_y;
	def_button.length = length;
	def_button.on_press = on_press;
	return def_button;
}

menu def_menu;
menu test_menu;

menu menu_instantiate(uint32_t size_x, uint32_t size_y, uint16_t *data, void (*menu_update)(menu *m, ...))
{
	def_menu = size_x;
	def_menu = size_y;
	def_menu.data = data;
	def_menu.instantiate = menu_instantiate;
	def_menu.deconstruct = menu_deconstruct;
	def_menu.update = menu_update;
	return def_menu;
}

menu new_menu(uint32_t size_x, uint32_t size_y, uint16_t *data)
{
	def_menu = size_x;
	def_menu = size_y;
	def_menu.data = data;
	def_menu.instantiate = menu_instantiate;
	def_menu.deconstruct = menu_deconstruct;
	def_menu.update = menu_update;
	return def_menu;
}

void menu_deconstruct(menu *m)
{
	//calloc(m, sizeof(menu)); since we don't currently allow for the deconstruction of variables (plus there isn't a need to yet), we will revisit this later. until then...:
	return;
}

void def_menu_update(menu *m)
{
	printf("wow, idiot. This is just a placeholder. fucking idiot.\n");
}

typedef struct window {
	uint32_t size_x;
	uint32_t size_y;
	uint32_t offset_x;
	uint32_t offset_y;
	
	list buttons;
	
	menu mdata;
	bool priority;
	
	window (*instantiate)(uint32_t, uint32_t, uint32_t, uint32_t, menu, list buttons, void (*)(window*));
	void (*deconstruct)(window*);
	void (*update)(window*, ...);
	void (*load)(window*);
	void (*unload)(window*);
} window;

window window_instantiate(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*));
window new_window(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*));
void window_deconstruct(window *w);
void def_window_update(window *w);
void def_window_load(window *w);
void def_window_unload(window *w);
uint32_t get_larger_button_x(window *w, list b);
uint32_t get_larger_button_y(window *w, list b);
uint32_t get_smaller_button_x(window *w, list b);
uint32_t get_smaller_button_y(window *w, list b);

window def_window;
window test_window;
window priority_window;

window window_instantiate(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*))
{
	def_window.size_x = size_x;
	def_window.size_y = size_y;
	def_window.offset_x = offset_x;
	def_window.offset_y = offset_y;
	def_window.current_highlighted_button_x = 0;
	def_window.current_highlighted_button_y = 0;
	def_window.mdata = mdata;
	def_window.buttons = buttons;
	def_window.priority = 0;
	def_window.instantiate = new_window;
	def_window.deconstruct = window_deconstruct;
	def_window.update = def_window_update;
	def_window.load = def_window_load;
	def_window.unload = def_window_unload;
	def_window.get_larger_button_x = get_larger_button_x;
	def_window.get_larger_button_y = get_larger_button_y;
	def_window.get_smaller_button_x = get_smaller_button_x;
	def_window.get_smaller_button_y = get_smaller_button_y;
	for(int x = 0; x < buttons.count; x++) {
		button *b = buttons.get(&buttons, x+1);
		b->old_background_color = mdata.data[b->loc_x + (b->loc_y * TERMINAL_X)] & 0xF000;
	}
	return def_window;
}

window new_window(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*))
{
	def_window.size_x = size_x;
	def_window.size_y = size_y;
	def_window.offset_x = offset_x;
	def_window.offset_y = offset_y;
	def_window.current_highlighted_button_x = 0;
	def_window.current_highlighted_button_y = 0;
	def_window.mdata = mdata;
	def_window.buttons = buttons;
	def_window.priority = 0;
	def_window.instantiate = new_window;
	def_window.deconstruct = window_deconstruct;
	def_window.update = update;
	def_window.load = def_window_load;
	def_window.unload = def_window_unload;
	def_window.get_larger_button_x = get_larger_button_x;
	def_window.get_larger_button_y = get_larger_button_y;
	def_window.get_smaller_button_x = get_smaller_button_x;
	def_window.get_smaller_button_y = get_smaller_button_y;
	return def_window;
}

void window_deconstruct(window *w)
{
	printf("wow, idiot. This is just a placeholder. fucking idiot.\n");
}

void def_window_update(window *w)
{
	for(int y = w->offset_y; y < (w->offset_y + w->size_y); y++) {
		for(int x = w->offset_x; x < (w->offset_x + w->size_x); x++) {
			memsetw(0xB8000, mdata.data[y * TERMINAL_X + x], 1);
		}
	}
}

void def_window_load(window *w)
{
	w->priority = true;
	priority_window = *w;
	keyboard_driver_state = 1;
	for(int y = w->offset_y; y < (w->offset_y + w->size_y); y++) {
		for(int x = w->offset_x; x < (w->offset_x + w->size_x); x++) {
			memsetw(0xB8000, mdata.data[y * TERMINAL_X + x], 1);
		}
	}
}

void def_window_unload(window *w) 
{
	w->priority = false;
}

uint32_t get_larger_button_x(window *w, list b)
{
	uint32_t current = 0;
	for(int i = 0; i < b.count; i++) {
		if(!i) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_x;
		}
		if( (((button *) b.get(&(w->buttons), i+1))->loc_x >  w->current_highlighted_button_x) && (((button *) b.get(&(w->buttons), i+1))->loc_x <= current) ) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_x;
		}
	}
	if(!current) {
		return ~(0);
	}
	return current;
}

uint32_t get_larger_button_y(window *w, list b)
{
	uint32_t current = 0;
	for(int i = 0; i < b.count; i++) {
		if(!i) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_x;
		}
		if( (((button *) b.get(&(w->buttons), i+1))->loc_y >  w->current_highlighted_button_y) && (((button *) b.get(&(w->buttons), i+1))->loc_y <= current) ) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_y;
		}
	}
	if(!current) {
		return ~(0);
	}
	return current;
}

uint32_t get_smaller_button_x(window *w, list b)
{
	uint32_t current = 0;
	for(int i = 0; i < b.count; i++) {
		if(!i) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_x;
		}
		if( (((button *) b.get(&(w->buttons), i+1))->loc_x <  w->current_highlighted_button_x) && (((button *) b.get(&(w->buttons), i+1))->loc_x >= current) ) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_x;
		}
	}
	if(!current) {
		return ~(0);
	}
	return current;
}

uint32_t get_smaller_button_y(window *w, list b)
{
	uint32_t current = 0;
	for(int i = 0; i < b.count; i++) {
		if(!i) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_y;
		}
		if( (((button *) b.get(&(w->buttons), i+1))->loc_y <  w->current_highlighted_button_y) && (((button *) b.get(&(w->buttons), i+1))->loc_y >= current) ) {
			current = ((button *) b.get(&(w->buttons), i+1))->loc_y;
		}
	}
	if(!current) {
		return ~(0);
	}
	return current;
}

console def_console;
console test_console;

console new_console(void (**commands)(char*, uint32_t), uint32_t no_commands, short color, list prev_commands, char *label);
void console_deconstruct(console *c);
void def_console_update(console* c);
void def_console_load(console *c);
void def_console_unload(console *c);

console new_console(command_function *commands, uint32_t no_commands, short color, list prev_commands, char *label)
{
	def_console.size_x = TERMINAL_X;
	def_console.size_y = TERMINAL_Y;
	def_console.offset_x = 0;
	def_console.offset_y = 0;
	def_console.priority = 0;
	def_console.cursor_x = 0;
	def_console.cursor_y = strlen(label) + 1;
	def_console.org_x = strlen(label) + 1;
	def_console.org_y = 0;
	def_console.current_command = (char *) smalloc(256, 1);
	def_console.label = label;
	def_console.color = color;
	def_console.commands = commands;
	def_console.command_no = 1;
	def_console.length_of_current_command = 0;
	def_console.prev_commands = prev_commands;
	def_console.instantiate = new_console;
	def_console.deconstruct = console_deconstruct;
	def_console.update = def_console_update;
	def_console.load = def_console_load;
	def_console.unload = def_console_unload;
	return def_console;
}

void console_deconstruct(console *c)
{
	printf("wow, idiot. This is just a placeholder. fucking idiot.\n");
}

void def_console_update(console *c)
{
	//who knows. 
	return;
}

void def_console_load(console *c)
{
	c->priority = true;
	priority_window = *c;
	keyboard_driver_state = 2;
	for(int y = c->offset_y; y < (c->offset_y + c->size_y); y++) {
		for(int x = w->offset_c; x < (c->offset_x + c->size_x); x++) {
			memsetw(0xB8000, mdata.data[y * TERMINAL_X + x], 1);
		}
	}
}

void def_console_unload(console *c)
{
	c->priority = false;
}

typedef struct map {
	uint32_t size_x; //greater than or equal to 80
	uint32_t size_y; //greater than or equal to 25
	uint32_t offset_x; //always 0
	uint32_t offset_y; //always 0
	uint32_t current_highlighted_x; //here for getting mouse position
	uint32_t current_highlighted_y; //see above
	
	bool priority;
	
	menu mdata;
	window (*instantiate)(uint32_t, uint32_t, menu);
	void (*deconstruct)(map*);
	void (*update)(map*);
	void (*load)(map*);
	void (*unload)(map*);
} map;

map def_map;
map test_map;

map new_map(uint32_t size_x, uint32_t size_y, map mdata);
void map_deconstruct(map *m);
void def_map_update(map *m);
void def_map_load(map *m);
void def_map_unload(map *m);

map new_map(uint32_t size_x, uint32_t size_y, map mdata)
{
	def_map.size_x = size_x;
	def_map.size_y = size_y;
	def_map.offset_x = 0;
	def_map.offset_y = 0;
	def_map.current_highlighted_x = 0;
	def_map.current_highlighted_y = 0;
	def_map.mdata = mdata;
	def_map.instantiate = new_map;
	def_map.deconstruct = map_deconstruct;
	def_map.update = def_map_update;
	def_map.load = def_map_load;
	def_map.unload = def_map_unload;
	return def_map;
}

void map_deconstruct(map *m)
{
	printf("wow, idiot. This is just a placeholder. fucking idiot.\n");
}

void map_update(map *m)
{
	//nothing to update
	return;
}

void def_map_load(map *m) 
{
	m->priority = true;
	priority_window = *m;
	keyboard_driver_state = 3;
	for(int y = m->offset_y; y < (m->offset_y + m->size_y); y++) {
		for(int x = w->offset_c; x < (m->offset_x + m->size_x); x++) {
			memsetw(0xB8000, mdata.data[y * TERMINAL_X + x], 1);
		}
	}
}

void def_map_unload(map *m)
{
	m->priority = false;
}

