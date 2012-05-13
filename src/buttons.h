/*
 * @Author  : Simon Fojtu
 * @Date    : 13.06.2011
 */

#ifndef __BUTTONS_H_
#define __BUTTONS_H_

#include <avr/io.h>
#include "defs.h"

enum {
        B_UP,
        B_DOWN,
        B_MODE,
        BUTTONS_COUNT
};

enum {
        EVT_KEY_PRESSED,
        EVT_KEY_RELEASED,
        EVT_KEY_HELD,
        EVT_COUNT
};

void buttons_init(void);
void buttons_update(void);
uint8_t get_button_f(unsigned char);
uint8_t get_button(unsigned char);

void Keyboard_tick(status_t *stat_);
void Keyboard_init(void);

#endif

