/**
 *
 * Copyright 2017 Brandon A Koerner
 * https://github.com/ReewassSquared/OSMIUM
 * Licensed under the Apache License 2.0
 *
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

extern bool lshft;
extern bool rshft;
extern bool lctrl;
extern bool lalt;
extern bool delete_;
extern bool insert_;

extern bool numlock;
extern bool scrolllock;
extern bool capslock;

extern bool default_keyboard_modifier;
extern bool keyboard_modifier_list_arrow;
extern unsigned int num_of_entries;

extern void lights();
extern void disable_key_interrupts();
extern void enable_key_interrupts();
extern uint32_t __volatile__ keyboard_driver_state;
extern void keyboard_init();

#endif