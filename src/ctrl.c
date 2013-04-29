/*
 * @Author  : Simon Fojtu
 * @Date    : 24.06.2011
 */

#include "ctrl.h"
#include "3310_routines.h"
#include <stdlib.h>

void ctrl_init(Ctrl *c)
{
	/* Write initialization routine here */

	/* output pin */
	DDRD |= 1<<PD5;

	c->e_sum = 0;
	c->t0 = -1;
}

void ctrl_tick(Ctrl *c, Context *ctx)
{
	char action;


	switch (ctx->ctrl_mode) {
	case CTRL_OFF:
		action = 0;
		break;

        case CTRL_HYST:
                action = (ctx->t1_sp - ctx->t1 > 1) ? 1 : 0;
		break;
                
        case CTRL_MAX:
                // to keep compiler quiet about not handling CTRL_MAX in the switch
                break;
	}

	if (action)
		PORTD |= 1<<PD5;
        else
		PORTD &= ~(1<<PD5);
}

