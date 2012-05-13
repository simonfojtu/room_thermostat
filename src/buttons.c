/*
 * @Author  : Simon Fojtu
 * @Date    : 13.06.2011
 */

#include "defs.h"
#include "buttons.h"
#include "fsm.h"

#include <avr/io.h>

/*
 * state of the buttons
 * UP, DOWN, MODE
 */
uint8_t buttons_state[BUTTONS_COUNT];
uint8_t last[BUTTONS_COUNT];

void buttons_init(void)
{
        INIT_BUTTONS_PINS;
}

void buttons_update(void)
{
        /* TODO check correct wiring */
        buttons_state[B_UP]     = (buttons_state[B_UP]    << 1) | UP_PRESSED;
        buttons_state[B_DOWN]   = (buttons_state[B_DOWN]  << 1) | DOWN_PRESSED;
        buttons_state[B_MODE]   = (buttons_state[B_MODE]  << 1) | MODE_PRESSED;
}

uint8_t get_button_f(unsigned char which)
{
        return buttons_state[which];
}

uint8_t get_button(unsigned char which)
{
        return (buttons_state[which] & 0x01);
}

typedef struct Keyboard Keyboard;
struct Keyboard {
        Fsm super_;
        status_t *stat;
};

Keyboard keyboard;

void KeyboardCtor(Keyboard *me);
void Keyboard_initial(Keyboard *me, Event const *e);
void Keyboard_default(Keyboard *me, Event const *e);
void Keyboard_setting_sp(Keyboard *me, Event const *e);
void Keyboard_setting_timer(Keyboard *me, Event const *e);
void Keyboard_setting_mode(Keyboard *me, Event const *e);

typedef struct KbdEvent KbdEvent;
struct KbdEvent {
        Event super_;
        char code;
};

typedef struct KbdEvtQueue KbdEvtQueue;
struct KbdEvtQueue {
        int size;
        KbdEvent queue[KBD_EVT_QUEUE_SIZE];
};

KbdEvtQueue kbdEvtQueue;

void KeyboardCtor(Keyboard *me)
{
        FsmCtor_(&me->super_, &Keyboard_initial);
}

void Keyboard_initial(Keyboard *me, Event const *e)
{
        FsmTran_((Fsm *)me, &Keyboard_default);
}

void Keyboard_default(Keyboard *me, Event const *e)
{
        switch (e->sig) {
        case EVT_KEY_PRESSED:
                switch (((KbdEvent *)e)->code) {
                case B_UP:
                        me->stat->t1_sp += 1;
                        me->stat->ctrl_mode = CTRL_MAN;
                        break;
                case B_DOWN:
                        me->stat->t1_sp -= 1;
                        me->stat->ctrl_mode = CTRL_MAN;
                        break;
                case B_MODE:
                        if (me->stat->ctrl_mode < CTRL_MAX - 1)
                                me->stat->ctrl_mode++;
                        else
                                me->stat->ctrl_mode = 0;
                        break;
                }
                break;

        case EVT_KEY_HELD:
                switch (((KbdEvent *)e)->code) {
                case B_UP:
                        me->stat->t1_sp += 1;
                        me->stat->ctrl_mode = CTRL_MAN;
                        break;
                case B_DOWN:
                        me->stat->t1_sp -= 1;
                        me->stat->ctrl_mode = CTRL_MAN;
                        break;

                }
        }
}

void Keyboard_tick(status_t * stat_)
{
        /*
         * Generate events
         */
        unsigned char i;
        /* update buttons state */
        buttons_update();
        for (i = 0; i < BUTTONS_COUNT; i++) {
                if (kbdEvtQueue.size == KBD_EVT_QUEUE_SIZE)
                        break;

                /* Rising edge or key held*/
                if (get_button(i)) {
                        Event e;
                        e.sig = (last[i] ? EVT_KEY_HELD : EVT_KEY_PRESSED);
                        KbdEvent nke;
                        nke.super_ = e;
                        nke.code = i;
                        kbdEvtQueue.queue[kbdEvtQueue.size] = nke;
                        kbdEvtQueue.size++;
                }
                last[i] = get_button(i);
        }

        /* get event */
        if (kbdEvtQueue.size == 0)
                return;

        KbdEvent ke = kbdEvtQueue.queue[0];

        for (i = 0; i < kbdEvtQueue.size - 1; i++) {
                kbdEvtQueue.queue[i] = kbdEvtQueue.queue[i+1];
        }
        kbdEvtQueue.size--;

        /* Dispatch the event */
        keyboard.stat = stat_;
        FsmDispatch((Fsm *)&keyboard, (Event *)&ke);
}

void Keyboard_init(void)
{
        KeyboardCtor(&keyboard);
        FsmInit((Fsm *)&keyboard, 0);
        buttons_init();
}

