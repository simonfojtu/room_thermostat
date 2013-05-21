/*
 * @Author  : Simon Fojtu
 * @Date    : 24.06.2011
 */

#include "ctrl.h"
#include "3310_routines.h"
#include <stdlib.h>

void ctrl_init(void)
{
	/* output pin */
	DDRD |= 1<<PD5;
}

void ctrl_tick(Context *ctx)
{
	char action = 0;

        int16_t now;

	switch (ctx->ctrl_mode) {
	case(CTRL_OFF):
		action = 0;
		break;

        case(CTRL_HYST):
                action = (ctx->t1_sp - ctx->t1 > 1) ? 1 : 0;
		break;

        case(CTRL_AUTO):
                now = (ctx->min + ctx->t_offset) % (24*60);
                for (unsigned int i = 0; i < PROG_ENTRIES_COUNT; i++) {
                        if (now == ctx->progEntries[i].min) {
                                ctx->t1_sp = ctx->progEntries[i].temp;
                        }
                }
                action = (ctx->t1_sp - ctx->t1 > 1) ? 1 : 0;
                break;
                
        case(CTRL_MAX):
                // to keep compiler quiet about not handling CTRL_MAX in the switch
                break;
	}

	if (action)
		PORTD |= 1<<PD5;
        else
		PORTD &= ~(1<<PD5);
}

