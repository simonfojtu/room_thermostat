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
uint8_t button_pressed[BUTTONS_COUNT];
uint16_t buttons[BUTTONS_COUNT];

void buttons_init(void)
{
	// vstupni PC2 - PC4
	DDRC &= ~((1<<PC2) | (1<<PC3) | (1<<PC4));
}

void buttons_update(void)
{
	/* according to wiring */
	button_pressed[B_UP]	= ((PINC & 1<<PC2) == 0);
	button_pressed[B_DOWN]	= ((PINC & 1<<PC4) == 0);
	button_pressed[B_MENU]	= ((PINC & 1<<PC3) == 0);
}

void KeyboardCtor(Context *ctx);
void Keyboard_initial(Context *ctx, Event const *e);
void Keyboard_default(Context *ctx, Event const *e);
void Keyboard_setting_sp(Context *ctx, Event const *e);
void Keyboard_setting_time_h(Context *ctx, Event const *e);
void Keyboard_setting_time_m(Context *ctx, Event const *e);
void Keyboard_setting_prog(Context *ctx, Event const *e);
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
			FsmTran_((Fsm *)ctx, &Keyboard_setting_time_h);
                        ctx->fsm_state = FSM_HOUR;
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
        eeprom_write_dword((uint32_t *)EEPROM_T1, ctx->t1_sp + 0xffff); // -> uint32
}


void Keyboard_setting_time_h(Context *ctx, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t_offset+=60;
			break;
                case B_DOWN:
                        ctx->t_offset-=60;
                        break;
		case B_MENU:
			FsmTran_((Fsm *)ctx, &Keyboard_setting_time_m);
                        ctx->fsm_state = FSM_MIN;
			break;
		}
                break;
        case EVT_KEY_HELD:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t_offset+=60;
			break;
                case B_DOWN:
                        ctx->t_offset-=60;
                        break;
		}
	}
        if (ctx->t_offset < 0)
                ctx->t_offset += 60*24;
        if (ctx->t_offset >= 60*24)
                ctx->t_offset -= 60*24;
}

void Keyboard_setting_time_m(Context *ctx, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t_offset+=1;
			break;
                case B_DOWN:
                        ctx->t_offset-=1;
                        break;
		case B_MENU:
			FsmTran_((Fsm *)ctx, &Keyboard_setting_prog);
                        ctx->fsm_state = FSM_PROG;
			break;
		}
                break;
        case EVT_KEY_HELD:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        ctx->t_offset+=1;
			break;
                case B_DOWN:
                        ctx->t_offset-=1;
                        break;
		}
                break;
	}
        if (ctx->t_offset < 0)
                ctx->t_offset += 60*24;
        if (ctx->t_offset >= 60*24)
                ctx->t_offset -= 60*24;
}

void Keyboard_setting_prog(Context *ctx, Event const *e)
{
	switch (e->sig) {
	case EVT_KEY_PRESSED:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        switch (ctx->thm) {
                                case 0: // temperature
                                        ctx->progEntries[ctx->entry_id].temp+=5;
                                        break;
                                case 1: // hour
                                        ctx->progEntries[ctx->entry_id].min+=60;
                                        break;
                                case 2: // minute
                                        ctx->progEntries[ctx->entry_id].min+=10;
                                        break;
                        }
                        if (ctx->progEntries[ctx->entry_id].min >= 60*24)
                                ctx->progEntries[ctx->entry_id].min -= 60*24;
			break;
                case B_DOWN:
                        switch (ctx->thm) {
                                case 0: // temperature
                                        ctx->progEntries[ctx->entry_id].temp-=5;
                                        break;
                                case 1: // hour
                                        ctx->progEntries[ctx->entry_id].min-=60;
                                        break;
                                case 2: // minute
                                        ctx->progEntries[ctx->entry_id].min-=10;
                                        break;
                        }
                        if (ctx->progEntries[ctx->entry_id].min < 0)
                                ctx->progEntries[ctx->entry_id].min += 60*24;
                        break;
		case B_MENU:
                        ctx->thm++;
                        if (ctx->thm == 3) {
                                ctx->thm = 0;
                                ctx->entry_id++;
                        }
                        if (ctx->entry_id == PROG_ENTRIES_COUNT) {
                                ctx->entry_id = 0;
        			FsmTran_((Fsm *)ctx, &Keyboard_setting_onoff);
                                ctx->fsm_state = FSM_MODE;

                                for (uint8_t i = 0; i < PROG_ENTRIES_COUNT; i++) {
                                        eeprom_write_dword((uint32_t *)EEPROM_PE + 8*i, ctx->progEntries[i].temp + 0xffff); // -> uint32
                                        eeprom_write_dword((uint32_t *)EEPROM_PE + 8*i + 4, ctx->progEntries[i].min + 0xffff); // -> uint32
                                }
                        }
			break;
		}
                break;
        case EVT_KEY_HELD:
		switch (((KbdEvent *)e)->code) {
		case B_UP:
                        switch (ctx->thm) {
                                case 0: // temperature
                                        ctx->progEntries[ctx->entry_id].temp+=5;
                                        break;
                                case 1: // hour
                                        ctx->progEntries[ctx->entry_id].min+=60;
                                        break;
                                case 2: // minute
                                        ctx->progEntries[ctx->entry_id].min+=10;
                                        break;
                        }
                        if (ctx->progEntries[ctx->entry_id].min >= 60*24)
                                ctx->progEntries[ctx->entry_id].min -= 60*24;
			break;
                case B_DOWN:
                        switch (ctx->thm) {
                                case 0: // temperature
                                        ctx->progEntries[ctx->entry_id].temp-=5;
                                        break;
                                case 1: // hour
                                        ctx->progEntries[ctx->entry_id].min-=60;
                                        break;
                                case 2: // minute
                                        ctx->progEntries[ctx->entry_id].min-=10;
                                        break;
                        }
                        if (ctx->progEntries[ctx->entry_id].min < 0)
                                ctx->progEntries[ctx->entry_id].min += 60*24;
                        break;
                case B_MENU:
                        ctx->entry_id = 0;
                        ctx->thm = 0;
			FsmTran_((Fsm *)ctx, &Keyboard_setting_sp);
                        ctx->fsm_state = FSM_MODE;
                        for (uint8_t i = 0; i < PROG_ENTRIES_COUNT; i++) {
                                eeprom_write_dword((uint32_t *)EEPROM_PE + 8*i, ctx->progEntries[i].temp + 0xffff); // -> uint32
                                eeprom_write_dword((uint32_t *)EEPROM_PE + 8*i + 4, ctx->progEntries[i].min + 0xffff); // -> uint32
                        }
                        break;
		}
                break;
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
                        ctx->fsm_state = FSM_SP;
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
                if (button_pressed[i])
                        buttons[i]++;
                else
                        buttons[i] = 0;


		/* Rising edge */
		if (buttons[i] == 1) {
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
                if (buttons[i] > BUTTON_HELD_TIMEOUT) {
                        buttons[i] = 1;
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

