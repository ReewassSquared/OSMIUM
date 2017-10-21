/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdlib.h> //standard library stuff like types and string.h (assuming already provided).
#indlude <vgalib.h> //provides things like TERMINAL_X, TERMINAL_Y, NORMAL_BACKGROUND_COLOR and stuff (assuming already provided)
#include <print.h> //assuming a print.h-type function has been provided as well as change_color function
#include <list.h> //mine
#include <keyboard.h> //NOTE: ADD SET_KEYBOARD_MODE() AND WINDOW_BUTTON_MODE AND CONSOLE_CMD_MODE (mine)

typedef void (*command_function)(char*, uint32_t);

typedef struct __attribute__ ((packed)) button {
	uint32_t loc_x;
	uint32_t loc_y;
	uint32_t length;
	bool priority;
	short old_background_color;
	
	button (*instantiate)(uint32_t, uint32_t, uint32_t, void (*)(button*));
	void (*on_press)(button*);
} button;

extern button def_button;
extern button test_button;

extern button new_button(uint32_t loc_x, uint32_t loc_y, uint32_t length, void (*on_press)(button*));

typedef struct __attribute__ ((packed)) scdata {
	uint8_t color;
	uint8_t char;
} scdata;

typedef struct menu {
	uint32_t size_x;
	uint32_t size_y;
	uint16_t *data;
	
	menu (*instantiate)(uint32_t, uint32_t, uint16_t*);
	void (*deconstruct)(menu*);
	void (*update)(menu*);
} menu;

extern menu menu_instantiate(uint32_t size_x, uint32_t size_y, uint16_t *data);
extern menu new_menu(uint32_t size_x, uint32_t size_y, uint16_t *data);
extern void menu_deconstruct(menu *m);
extern void def_menu_update(menu *m);

extern menu def_menu;
extern menu test_menu;

typedef struct window {
	uint32_t size_x;
	uint32_t size_y;
	uint32_t offset_x;
	uint32_t offset_y;
	uint32_t current_highlighted_button_x; //don't need to be used but are here for convenience
	uint32_t current_highlighted_button_y; //aren't necessary for code so far but can be set
	uint32_t active_button_index; //standard for getting active button
	
	list buttons;
	
	menu mdata;
	bool priority;
	
	window (*instantiate)(uint32_t, uint32_t, uint32_t, uint32_t, menu, list, void (*)(window*));
	void (*deconstruct)(window*);
	void (*update)(window*);
	void (*load)(window*);
	void (*unload)(window*);
	uint32_t (*get_larger_button_x)(window*, list);
	uint32_t (*get_larger_button_y)(window*, list);
	uint32_t (*get_smaller_button_x)(window*, list);
	uint32_t (*get_smaller_button_y)(window*, list);
} window;

extern window window_instantiate(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*));
extern window new_window(uint32_t size_x, uint32_t size_y, uint32_t offset_x, uint32_t offset_y, menu mdata, list buttons, void (*update)(window*));
extern void window_deconstruct(window *w);
extern void def_window_update(window *w);
extern void def_window_load(window *w);
extern void def_window_unload(window *w);
extern uint32_t get_larger_button_x(window *w, list b);
extern uint32_t get_larger_button_y(window *w, list b);
extern uint32_t get_smaller_button_x(window *w, list b);
extern uint32_t get_smaller_button_y(window *w, list b);

extern window def_window;
extern void* priority_window; //this literally is something
extern window test_window;

typedef struct console { //extends the window class in a way
	uint32_t size_x; //always TERMINAL_X
	uint32_t size_y; //always TERMINAL_Y
	uint32_t offset_x; //always 0
	uint32_t offset_y; //always 0
	short color;
	bool priority;
	
	list prev_commands; //oooooooooo stores stuff!
	uint32_t command_no; //index in prev_commands loaded currently (unless prev_commands.count + 1)
	uint32_t no_commands;
	uint32_t length_of_current_command;
	char *current_command;
	
	char *label;
	
	uint32_t cursor_x;
	uint32_t cursor_y;
	uint32_t org_x;
	uint32_t org_y;
	
	command_function *commands;
	
	console (*instantiate)(command_function*, uint32_t, short, list, char*); //a pointer/buffer of function pointers that have parameters char* and uint32_t
	void (*deconstruct)(console*);
	void (*update)(console*);
	void (*load)(console*);
	void (*unload)(console*);
} console;

extern console def_console;
extern console test_console;

extern console new_console(command_function *commands, uint32_t no_commands, short color, list prev_commands, char *label);
extern void console_deconstruct(console *c);
extern void def_console_update(console* c);
extern void def_console_load(console *c);
extern void def_console_unload(console *c);

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

extern map def_map;
extern map test_map;

extern map new_map(uint32_t size_x, uint32_t size_y, map mdata);
extern void map_deconstruct(map *m);
extern void def_map_update(map *m);
extern void def_map_load(map *m);
extern void def_map_unload(map *m);

#endif