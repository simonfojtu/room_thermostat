/*
 * @Author  : Simon Fojtu
 * @Date    : 13.06.2011
 */

#include "buttons.h"
#include "fsm.h"
#include "eeprom.h"

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

void KeyboardCtor(Context *ctx);
void Keyboard_initial(Context *ctx, Event const *e);
void Keyboard_default(Context *ctx, Event const *e);
void Keyboard_setting_sp(Context *ctx, Event const *e);
void Keyboard_setting_time(Context *ctx, Event const *e);
void Keyboard_setting_onoff(Context *ctx, Event const *e);


void KeyboardCtor(Context *ctx)
{
	FsmCtor_(&ctx->fsm, &Keyboard_initial);
}

void Keyboard_initial(Context *ctx, Event const *e)
{
	FsmTran_(&ctx->fsm, &Keyboard_setting_sp);
}

/* Temperature setpoint setting */
void Keyboard_setting_sp(Context *ctx, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t1_sp+=5;
			break;
                case B_DOWN:
                        ctx->t1_sp-=5;
                        break;
		case B_MENU:
			FsmTran_((Fsm *)ctx, &Keyboard_setting_time);
			break;
		}
                break;
	case EVT_KEY_HELD:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t1_sp+=5;
			break;
                case B_DOWN:
                        ctx->t1_sp-=5;
                        break;
		}
                break;
	}
        /* Store temperature setpoint into eeprom */
        eeprom_write_dword(EEPROM_T1, ctx->t1_sp + 0xffff); // -> uint32
}


void Keyboard_setting_time(Context *ctx, Event const *e)
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
			FsmTran_((Fsm *)ctx, &Keyboard_setting_onoff);
			break;
		}
	}
}

void Keyboard_setting_onoff(Context *ctx, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->ctrl_mode = CTRL_HYST;
			break;
                case B_DOWN:
                        ctx->ctrl_mode = CTRL_OFF;
                        break;
		case B_MENU:
			FsmTran_((Fsm *)ctx, &Keyboard_setting_sp);
			break;
		}
	}
}

void Keyboard_tick(Context * ctx)
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
			if (ctx->kbdEvtQueue.size < EVENTS_QUEUE_MAX_SIZE - 1) {
				Event e;
				e.sig = EVT_KEY_PRESSED;
				KbdEvent nke;
				nke.super_ = e;
				nke.code = i;
				ctx->kbdEvtQueue.queue[ctx->kbdEvtQueue.size] = nke;
				ctx->kbdEvtQueue.size++;
			} else {
				// else drop the event
				break;
			}
		}
                /* Button held */
                if (get_button_f(i) == 0xff) {
                        buttons_state[i] = 0xfd; // 11111101b
			if (ctx->kbdEvtQueue.size < EVENTS_QUEUE_MAX_SIZE - 1) {
				Event e;
				e.sig = EVT_KEY_HELD;
				KbdEvent nke;
				nke.super_ = e;
				nke.code = i;
				ctx->kbdEvtQueue.queue[ctx->kbdEvtQueue.size] = nke;
				ctx->kbdEvtQueue.size++;
			} else {
				// else drop the event
				break;
			}
                }
		last[i] = get_button(i);
	}

	/* get event */
	if (ctx->kbdEvtQueue.size == 0)
		return;

	KbdEvent ke = ctx->kbdEvtQueue.queue[0];

	for (i = 0; i < ctx->kbdEvtQueue.size - 1; i++) {
		ctx->kbdEvtQueue.queue[i] = ctx->kbdEvtQueue.queue[i+1];
	}
	ctx->kbdEvtQueue.size--;

	/* Dispatch the event */
	FsmDispatch(&ctx->fsm, (Event *)&ke);
}

void Keyboard_init(Context * ctx)
{
	KeyboardCtor(ctx);
	FsmInit(&ctx->fsm, 0);
	buttons_init();
}

