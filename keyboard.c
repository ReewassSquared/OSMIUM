/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#include <graphics.h>

unsigned char keys_layout[128] =
{
	0,  27,
	'1', '2', '3', '4', '5', '6', '7', '8',
	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
 	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	 210,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   201,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   
	202,				/* Right shift */
	'*',  209,/* Alt */
	' ',	/* Space bar */
	200,/* Caps lock */
	211,/* 59 - F1 key ... > */
	212, 213, 214, 215, 216, 217, 218, 219,
	220,/* < 0... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,/* Home key */
	203,/* Up Arrow */
	0,/* Page Up */
	'-',
    	204,/* Left Arrow */
	0,
    	205,/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	206,/* Down Arrow */
	0,	/* Page Down */
	207,/* Insert Key */
	208,/* Delete Key */
	0,   0,   0, 221,/* F11 Key */
	222,/* F12 Key */
	0,	/* All other keys are undefined */
};		

unsigned char keys_layout_shft[128] =
{
	0,  27,
	'!', '@', '#', '$', '%', '^', '&', '*',
	/* 9 */
	'(', ')', '_', '+', '\b',	/* Backspace */
 	'\t',			/* Tab */
	'Q', 'W', 'E', 'R',	/* 19 */
	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
	 210,			/* 29   - Control */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
	'\"', '~',   201,		/* Left shift 42*/
	'|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
	'M', '<', '>', '\?',   
	202,				/* Right shift */
	'*',  209,/* Alt */
	' ',	/* Space bar */ 
	200,/* Caps lock */
	211,/* 59 - F1 key ... > */
	212, 213, 214, 215, 216, 217, 218, 219,
	220,/* < 0... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,/* Home key */
	203,/* Up Arrow */
	0,/* Page Up */
	'-', //74
    	204,/* Left Arrow */
	0,
    	205,/* Right Arrow */
	'+', //78
	0,	/* 79 - End key*/
	206,/* Down Arrow */
	0,	/* Page Down */
	207,/* Insert Key */
	208,/* Delete Key */
	0,   0,   0, 221,/* F11 Key */
	222,/* F12 Key */
	0,	/* All other keys are undefined */
};	

/* REAL QUICK:
I WANT TO SAY WHAT THE ACTUAL VALUES FOR THE UN-ASCII-FIED CHARACTERS ARE (AKA, SPECIAL CHARACTERS):
200 = CAPS LOCK
201 = LEFT SHIFT
202 = RGIHT SHIFT
203 = UP ARROW
204 = LEFT ARROW
205 = RIGHT ARROW
206 = DOWN ARROW
207 = INSERT
208 = DELETE
209 = ALT KEY
210 = CTRL KEY
211-222 = F1-F12
223 = ...*/

bool lshft;
bool rshft;
bool lctrl;
bool lalt;
bool delete_;
bool insert_;

bool numlock;
bool scrolllock;
bool capslock;

bool default_keyboard_modifier;
bool keyboard_modifier_list_arrow;
unsigned int num_of_entries;

void lights()
{
	if(numlock){
		if(capslock){
			if(scrolllock){
				outportb(0x64, 0xED);
				outportb(0x64, 0x7);
			}
			else {
				outportb(0x64, 0xED);
				outportb(0x64, 0x6);
			}
		}
		else if(scrolllock){
			outportb(0x64, 0xED);
			outportb(0x64, 0x3);
		}
		else {
			outportb(0x64, 0xED);
			outportb(0x64, 0x2);
		}
	}
	else if(scrolllock){
		if(capslock){
			outportb(0x64, 0xED);
			outportb(0x64, 0x5);
		}
		else {
			outportb(0x64, 0xED);
			outportb(0x64, 0x1);
		}
	}
	else if(capslock){
		outportb(0x64, 0xED);
		outportb(0x64, 0x4);
	}
}

void disable_key_interrupts()
{
	outportb(0x64, 0xF5);
}

void enable_key_interrupts()
{
	outportb(0x64, 0xF4);
}

void keyboard_handler_1(struct regs *r, unsigned char scancode)
{
	if(keys_layout[scancode] == 200) {
		capslock ^= 1;
	}
	if(keys_layout[scancode] == 201) {
		lshft ^= 1;
	}
	if(keys_layout[scancode] == 202) {
		rshft ^= 1;
	}
	if(keys_layout[scancode] == 207) {
		insert_ ^= 1;
	}
	if(keys_layout[scancode] == 208) {
		delete_ ^= 1;
	}
	if(keys_layout[scancode] == 209) {
		lalt ^= 1;
	}
	if(keys_layout[scancode] == 210) {
		lctrl ^= 1;
	}
	if( ( (scancode >= 0) && (scancode < 29) ) || ( (scancode >= 30) && (scancode < 42) ) || ( (scancode >= 43) && (scancode < 54) ) || (scancode == 74) || (scancode == 78) || (scancode == 55) || (scancode == 57) ) {
		if(capslock ^ lshft ^ rshft) {
			printf("%c", keys_layout_shft[scancode]);
		}
		else {
			printf("%c", keys_layout[scancode]);	
		}
	}
}

void keyboard_handler_2(struct regs *r, unsigned char scancode) {
	if(scancode == 203 || scancode == 204) {
		if(((window *) priority_window)->active_button_index == 0 || ((window *) priority_window)->active_button_index == 1) {
			return;
		}
		button *b = (button *) ((window *) priority_window)->buttons.get(&(((window *) priority_window)->buttons), ((window *) priority_window)->active_button_index);
		b->priority = false;
		uint32_t val = ((b->loc_x) + (b->loc_y * TERMINAL_X);
		for(short *i = (short *) (0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i < (short *) (length +0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i++) {
			i[val] = b->old_background_color | (0x0FFF & ((window *) priority_window)->mdata.data[val]);
			val++;
		}
		((window *) priority_window)->active_button_index--;
		b = (button *) ((window *) priority_window)->buttons.get(&(((window *) priority_window)->buttons), ((window *) priority_window)->active_button_index);
		b->priority = true;
		val = ((b->loc_x) + (b->loc_y * TERMINAL_X);
		for(short *i = (short *) (0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i < (short *) (length +0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i++) {
			i[val] = (((window *) priority_window)->mdata.data[val] & 0x0FFF) | 0x7000;
			val++;
		}
	}
	else if(scancode == 205 || scancode == 206) {
		if(((window *) priority_window)->active_button_index == ((window *) priority_window)->buttons.count) {
			return;
		}
		button *b = (button *) ((window *) priority_window)->buttons.get(&(((window *) priority_window)->buttons), ((window *) priority_window)->active_button_index);
		b->priority = false;
		uint32_t val = ((b->loc_x) + (b->loc_y * TERMINAL_X);
		for(short *i = (short *) (0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i < (short *) (length +0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i++) {
			i[val] = b->old_background_color | (0x0FFF & ((window *) priority_window)->mdata.data[val]);
			val++;
		}
		((window *) priority_window)->active_button_index++;
		b = (button *) ((window *) priority_window)->buttons.get(&(((window *) priority_window)->buttons), ((window *) priority_window)->active_button_index);
		b->priority = true;
		val = ((b->loc_x) + (b->loc_y * TERMINAL_X);
		for(short *i = (short *) (0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i < (short *) (length +0xB8000 + (b->loc_x) + (b->loc_y * TERMINAL_X)); i++) {
			i[val] = (((window *) priority_window)->mdata.data[val] & 0x0FFF) | 0x7000;
			val++;
		}
	}
	else if(keys_layout[scancode] == '\n') {
		if(((window *) priority_window)->active_button_index == 0) {
			return;
		}
		else {
			button *b = (button *) ((window *) priority_window)->buttons.get(&(((window *) priority_window)->buttons), ((window *) priority_window)->active_button_index);
			b->on_select();
		}
	}
}

void keyboard_handler_3(struct regs *r, unsigned char scancode) {
	(short *b_add) = (0xB8000); 
	if(keys_layout[scancode] == '\n' || strlen(((console *) priority_window)->current_command) > 255) {
		for(int x = 0; x < )
		printf("%c", '\n');
		bool no_command_match_found = true;
		for(int x = 0; x < ((console *) priority_window)->no_commands; x++) {
			if(cmd_strcmp(((console *) priority_window)->keywords[x], ((console *) priority_window)->current_command, strlen(keywords[x])) {
				no_command_match_found = false;
				((console *) priority_window)->commands[x](((console *) priority_window)->current_command, strlen(((console *) priority_window)->current_command));
			}
		}
		if(no_command_match_found) {
			if(strlen(((console *) priority_window)->current_command) >= 25) {
				printf("No command \"");
				for(int i = 0; i < 25; i++) {
					printf("%s", ((console *) priority_window)->current_command[i]);
				}
				printf("...\"found")
			}
			else {
				printf("No command \"%s\" found\n", ((console *) priority_window)->current_command)
			}
		}
		((console *) priority_window)->prev_commands.add(&(((console *) priority_window)->prev_commands), ((console *) priority_window)->current_command);
		printf( "%s%c", ((console *) priority_window)->label, '>');
		get_cursor_pos(&(((console *) priority_window)->org_x), &(((console *) priority_window)->org_y));
		get_cursor_pos(&(((console *) priority_window)->cursor_x), &(((console *) priority_window)->cursor_y));
		((console *) priority_window)->length_of_current_command = 0;
		((console *) priority_window)->current_command = (char *) smalloc(256, 1);
	}
	b_add += (short *)(((console *) priority_window)->org_x + (((console *) priority_window)->org_y * TERMINAL_X));
	else if(scancode == 203 || scancode == 204) {
		if(((console *) priority_window)->command_no == 1) {
			return;
		}
		((console *) priority_window)->command_no--;
		while(((console *) priority_window)->cursor_x != ((console *) priority_window)->org_x || ((console *) priority_window)->cursor_y != ((console *) priority_window)->org_y) {
			if(((console *) priority_window)->cursor_x == 0) {
				((console *) priority_window)->cursor_y--;
				((console *) priority_window)->cursor_x = TERMINAL_X;
			}
			((console *) priority_window)->cursor_x--;
			printf("%c", '\b');
		}
		((console *) priority_window)->current_command = (((console *) priority_window)->prev_commands).get(&((console *) priority_window)->prev_commands, ((console *) priority_window)->command_no);
		((console *) priority_window)->current_command[((console *) priority_window)->length_of_current_command] = strlen(current_command);
		printf(((console *) priority_window)->current_command);
		get_cursor_pos(&(((console *) priority_window)->cursor_x), &(((console *) priority_window)->cursor_y));
	}
	else if(scancode == 205 || scancode == 206) {
		if(((console *) priority_window)->command_no == ((console *) priority_window)->prev_commands.count + 1) {
			return;
		}
		((console *) priority_window)->command_no++;
		while(((console *) priority_window)->cursor_x != ((console *) priority_window)->org_x || ((console *) priority_window)->cursor_y != ((console *) priority_window)->org_y) {
			if(((console *) priority_window)->cursor_x == 0) {
				((console *) priority_window)->cursor_y--;
				((console *) priority_window)->cursor_x = TERMINAL_X;
			}
			((console *) priority_window)->cursor_x--;
			printf("%c", '\b');
		}
		((console *) priority_window)->current_command = (((console *) priority_window)->prev_commands).get(&((console *) priority_window)->prev_commands, ((console *) priority_window)->command_no);
		((console *) priority_window)->current_command[((console *) priority_window)->length_of_current_command] = strlen(current_command);
		printf(((console *) priority_window)->current_command);
		get_cursor_pos(&(((console *) priority_window)->cursor_x), &(((console *) priority_window)->cursor_y));
	}
	else {
		if(keys_layout[scancode] == 200) {
			capslock ^= 1;
		}
		if(keys_layout[scancode] == 201) {
			lshft ^= 1;
		}
		if(keys_layout[scancode] == 202) {
			rshft ^= 1;
		}
		if(keys_layout[scancode] == 207) {
			insert_ ^= 1;
		}
		if(keys_layout[scancode] == 208) {
			delete_ ^= 1;
		}
		if(keys_layout[scancode] == 209) {
			lalt ^= 1;
		}
		if(keys_layout[scancode] == 210) {
			lctrl ^= 1;
		}
		if( ( (scancode >= 0) && (scancode < 29) ) || ( (scancode >= 30) && (scancode < 42) ) || ( (scancode >= 43) && (scancode < 54) ) || (scancode == 74) || (scancode == 78) || (scancode == 55) || (scancode == 57) ) {
			if(capslock ^ lshft ^ rshft) {
				printf("%c", keys_layout_shft[scancode]);
				((console *) priority_window)->length_of_current_command++;
				((console *) priority_window)->current_command[((console *) priority_window)->length_of_current_command] = keys_layout_shft[scancode];
				get_cursor_pos(&(((console *) priority_window)->cursor_x), &(((console *) priority_window)->cursor_y));
			}
			else {
				printf("%c", keys_layout[scancode]);
				((console *) priority_window)->length_of_current_command++;
				((console *) priority_window)->current_command[((console *) priority_window)->length_of_current_command] = keys_layout[scancode];
				get_cursor_pos(&(((console *) priority_window)->cursor_x), &(((console *) priority_window)->cursor_y));				
			}
		}
	}
}

void keyboard_init()
{
	irq_install_handler(1, keyboard_handler);
	default_keyboard_modifier = true;
	keyboard_modifier_list_arrow = false;
	num_of_entries = 0;
	keychr = 0;
	lshft = false;
	rshft = false;
	lctrl = false;
	lalt = false;
	delete_ = false;

	numlock = false;
	scrolllock = false;
	capslock = false;
}

uint32_t __volatile__ keyboard_driver_state = 0;

void keyboard_handler(struct regs *r) {
	unsigned char scancode = inb(0x60);
	switch keyboard_driver_state {
		case 0: 
			keyboard_handler_1(r, scancode);
		case 1:
			keyboard_handler_2(r, scancode);
		case 2:
			keyboard_handler_3(r, scancode);
		default:
			keyboard_handler_1(r, scancode);

	}
}
