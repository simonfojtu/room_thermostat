/*
 * @Author  : Simon Fojtu
 * @Date    : 13.06.2011
 */

#include "buttons.h"
#include "fsm.h"
#include "eeprom.h"

#define KBD_EVT_QUEUE_SIZE 10

/*
 * state of the buttons
 * UP, DOWN, MENU 
 */
uint8_t buttons_state[BUTTONS_COUNT];
uint8_t last[BUTTONS_COUNT];

void buttons_init(void)
{
	// vstupni PC2 - PC4
	DDRC &= ~((1<<PC2) | (1<<PC3) | (1<<PC4));
}

void buttons_update(void)
{
	/* according to wiring */
	buttons_state[B_UP]	= (buttons_state[B_UP]    << 1) | ((PINC & 1<<PC2) == 0);
	buttons_state[B_DOWN]	= (buttons_state[B_DOWN]  << 1) | ((PINC & 1<<PC4) == 0);
	buttons_state[B_MENU]	= (buttons_state[B_MENU] << 1) | ((PINC & 1<<PC3) == 0);
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
void Keyboard_setting_time(Keyboard *me, Event const *e);

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
	FsmTran_((Fsm *)me, &Keyboard_setting_sp);
}

/* Temperature setpoint setting */
void Keyboard_setting_sp(Keyboard *me, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        me->stat->t1_sp+=5;
			break;
                case B_DOWN:
                        me->stat->t1_sp-=5;
                        break;
		case B_MENU:
			FsmTran_((Fsm *)me, &Keyboard_setting_time);
			break;
		}
	}
        /* Store temperature setpoint into eeprom */
        eeprom_write_dword(EEPROM_T1, me->stat->t1_sp + 0xffff); // -> uint32
}


void Keyboard_setting_time(Keyboard *me, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        // TODO
			break;
                case B_DOWN:
                        // TODO
                        break;
		case B_MENU:
			FsmTran_((Fsm *)me, &Keyboard_setting_sp);
			break;
		}
	}
}

void Keyboard_tick(status_t * stat_)
{
	/*
	 * Generate events
	 */
	int i;
	/* update buttons state */
	buttons_update();
	for (i = 0; i < BUTTONS_COUNT; i++) {

		/* Rising edge */
		if ((!last[i]) && (get_button(i))) {
			if (kbdEvtQueue.size < EVENTS_QUEUE_MAX_SIZE - 1) {
				Event e;
				e.sig = EVT_KEY_PRESSED;
				KbdEvent nke;
				nke.super_ = e;
				nke.code = i;
				kbdEvtQueue.queue[kbdEvtQueue.size] = nke;
				kbdEvtQueue.size++;
			} else {
				// else drop the event
				break;
			}
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

